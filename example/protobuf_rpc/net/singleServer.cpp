﻿/*
 * Tencent is pleased to support the open source community by making Pebble available.
 * Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.
 * Licensed under the MIT License (the "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT
 * Unless required by applicable law or agreed to in writing, software distributed under the License
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the License for the specific language governing permissions and limitations under
 * the License.
 *
 */

#include <cstdio>
#include <iostream>
#include <sstream>

#include "singleServer.hpp"

#define ASSERT_EQ(expected, actual) \
    if ((expected) != (actual)) { \
        fprintf(stderr, "(%s:%d)(%s) %d != %d\n", __FILE__, __LINE__, __FUNCTION__, (expected), (actual)); \
        exit(1); \
    }

void usage() {
    std::cout << "usage   : ./server url" << std::endl
              << "default : url = tcp://127.0.0.1:8888" << std::endl;
}

singleServer* singleServer::ss = new singleServer();

singleServer::singleServer()
{
    // 初始化PebbleServer
    server = pebble::PebbleServer();
}

singleServer::~singleServer()
{

}

pebble::PebbleRpc* singleServer::getBinaryRpc()
{
    pebble::PebbleRpc* rpc = server.GetPebbleRpc(pebble::kPEBBLE_RPC_BINARY);
	return rpc;
}

singleServer* singleServer::getSingleServer()
{
    return ss;
}

int32_t singleServer::getLastMsgRoleID()
{
    int64_t handle = this->server.GetLastMessageInfo()->_remote_handle;
    return this->getRoleIDByHandle(handle);
}

void singleServer::bindRole2Handle(int32_t roleID)
{
    int64_t handle = this->server.GetLastMessageInfo()->_remote_handle;
    roleID2Handle[roleID] = handle;
    handle2RoleID[handle] = roleID;
}

int64_t singleServer::getHandleByRoleID(int32_t roleID)
{
    map<int32_t, int64_t>::iterator iter = this->roleID2Handle.find(roleID);
	if (iter == this->roleID2Handle.end())
	{
		return -1;
	}	
	return iter->second;
}

int32_t singleServer::getRoleIDByHandle(int64_t handle)
{
	map<int64_t, int32_t>::iterator iter = this->handle2RoleID.find(handle);
	if (iter == this->handle2RoleID.end())
	{
		return -1;
	}
	return iter->second;
}

int singleServer::setRecQueue(list< map<string, string>* >* queue)
{
    this->recQueue = queue;
    return 0;
}

int singleServer::setRecMutex(mutex* mt)
{
	this->recMutex = mt;
	return 0;
}

int singleServer::setRetQueue(list<needSaveMsg*>* queue)
{
	this->retQueue = queue;
	return 0;
}

int singleServer::setRetMutex(mutex* mt)
{
	this->retMutex = mt;
	return 0;
}

int singleServer::saveMsg(map<string, string>* newMsg)
{
    recQueue->push_back(newMsg);
    return 0;
}

int32_t commonCallBack(int32_t ret, const uint8_t* buff, uint32_t buff_len)
{
	printf("聊天消息回调\n");
	return 0;
}

int32_t singleServer::sendMsg(string function, int32_t roleID, uint8_t* buff, int32_t buff_len)
{
    int64_t handle = this->getHandleByRoleID(roleID);
	//二进制和JSON一样，都是二进制的thrift，只有PB才是正确结构
    //pebble::PebbleRpc* rpc = server.GetPebbleRpc(pebble::kPEBBLE_RPC_BINARY);
    pebble::PebbleRpc* rpc = server.GetPebbleRpc(pebble::kPEBBLE_RPC_PROTOBUF);
    stringstream ss;
    ss<<"rpcMsg:" << function;
std::cout << ss.str() << endl;

    ::pebble::RpcHead __head;
    __head.m_function_name.assign(ss.str());
    //__head.m_message_type = ::pebble::kRPC_ONEWAY;
    __head.m_message_type = ::pebble::kRPC_CALL;
    __head.m_session_id = 0;

	//这里的rsp是消息发送后util调用的回调函数，sendrequest本身的回调是util里定义的response，因此这里不能传空
    ::pebble::OnRpcResponse on_rsp = cxx::bind(commonCallBack, cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3);
    rpc->SendRequestSync(handle, __head, buff, buff_len, on_rsp, 10);
	return 0;
}


retStatus singleServer::broadcastMsg(string function, list<int32_t> roleIDList, uint8_t* buff, int32_t buff_len)
{
	list<int32_t>::iterator iter;
	for (iter = roleIDList.begin(); iter != roleIDList.end(); iter++)
	{
		this->sendMsg(function, *iter, buff, buff_len);
	}
	return rsSuccess;
}

int32_t On1sTimeout(singleServer* ss)
{
    std::lock_guard<std::mutex> guard(*(ss->retMutex));
    pebble::PebbleRpc* rpc = ss->getBinaryRpc();
    list<needSaveMsg*>::iterator msgIter;
	needSaveMsg* nsm;
    for(msgIter = ss->retQueue->begin(); msgIter != ss->retQueue->end(); msgIter++)
    {
        list<int32_t>::iterator roleIter;
	nsm = *msgIter;
        for(roleIter = nsm->roleIDList.begin(); roleIter != nsm->roleIDList.end(); roleIter++)
        {
            pebble::RpcHead head;
            int64_t handle = ss->getHandleByRoleID(*roleIter);
	    ::pebble::OnRpcResponse on_rsp;
		rpc->SendRequestSync(handle, head, nsm->buff, nsm->buff_len, on_rsp, 10);
        }
    }
    return 0;
}

void singleServer::setSendMsgTimer()
{
    // 创建定时器，定时向客户端推消息
    this->server.GetTimer()->StartTimer(1000, cxx::bind(On1sTimeout, this));
}

int singleServer::serverStart()
{
    int argc;
    const char** argv;
    usage();

    std::string url("tcp://0.0.0.0:8888");
    if (argc > 1) url.assign(argv[1]);

    int ret = server.Init();
    ASSERT_EQ(0, ret);

    // 添加传输
    int64_t handle = server.Bind(url);
    ASSERT_EQ(true, handle >= 0);

    // 获取PebbleRpc实例
    pebble::PebbleRpc* rpc = server.GetPebbleRpc(pebble::kPEBBLE_RPC_PROTOBUF);
    ASSERT_EQ(true, rpc != NULL);

    // 指定通道的处理器
    server.Attach(handle, rpc);

    // 添加服务
    rpcMsg rs;
    rs._server = this;

    ret = rpc->AddService(&rs);
    ASSERT_EQ(0, ret);

    server.Serve();

    return 0;
}



