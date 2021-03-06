// Generated by the Pebble C++ plugin 1.0.1.0 01:22:18 Nov  5 2018
// If you make any local change, they will be lost.
// source: example/protobuf_rpc/net/rpcMsg.proto

#include "rpcMsg.rpc.pb.h"

namespace example {

rpcMsgClient::rpcMsgClient(::pebble::PebbleRpc* rpc) {
    m_imp = new rpcMsgClientImp(rpc);
}

rpcMsgClient::~rpcMsgClient() { delete m_imp; }

void rpcMsgClient::SetHandle(int64_t handle) {
    m_imp->m_handle = handle;
}

void rpcMsgClient::SetRouteFunction(const cxx::function<int64_t(uint64_t key)>& route_callback) {
    m_imp->m_route_func = route_callback;
}

void rpcMsgClient::SetRouteKey(uint64_t route_key) {
    m_imp->m_route_key = route_key;
}

void rpcMsgClient::SetBroadcast(const std::string& channel_name) {
    m_imp->m_channel_name = channel_name;
}

int rpcMsgClient::SetTimeout(uint32_t timeout_ms, const char* method_name) {
    if (method_name != NULL) {
        cxx::unordered_map<std::string, uint32_t>::iterator it = m_imp->m_methods.find(method_name);
        if (it == m_imp->m_methods.end()) {
            return pebble::kRPC_UNSUPPORT_FUNCTION_NAME;
        }
        it->second = timeout_ms;
        return 0;
    }

    for (cxx::unordered_map<std::string, uint32_t>::iterator it = m_imp->m_methods.begin(); it != m_imp->m_methods.end(); ++it) {
        it->second = timeout_ms;
    }

    return 0;
}

int32_t rpcMsgClient::add(const ::example::CalRequest& request, ::example::CalResponse* response) {
    ::pebble::RpcHead __head;
    __head.m_function_name.assign("rpcMsg:add");
    __head.m_message_type = ::pebble::kRPC_CALL;
    __head.m_session_id = m_imp->m_client->GenSessionId();

    int __size = request.ByteSize();
    uint8_t* __buff = m_imp->m_client->GetBuffer(__size);
    if (__buff == NULL) {
        return ::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY;
    }

    if (!request.SerializeToArray(__buff, __size)) {
        return ::pebble::kRPC_ENCODE_FAILED;
    }

    if (m_imp->m_channel_name.empty()) {
        ::pebble::OnRpcResponse on_rsp = cxx::bind(&rpcMsgClientImp::recv_add_sync, m_imp,
            cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3, response);
        return m_imp->m_client->SendRequestSync(m_imp->GetHandle(), __head, __buff, __size, on_rsp, m_imp->m_methods["add"]);
    } else {
        return m_imp->m_client->BroadcastRequest(m_imp->m_channel_name, __head, __buff, __size);
    }

}

int32_t rpcMsgClient::Paralleladd(const ::example::CalRequest& request, int32_t* ret_code, ::example::CalResponse* response, uint32_t* num_called, uint32_t* num_parallel) {
    ::pebble::RpcHead __head;
    __head.m_function_name.assign("rpcMsg:add");
    __head.m_message_type = ::pebble::kRPC_CALL;
    __head.m_session_id = m_imp->m_client->GenSessionId();

    int __size = request.ByteSize();
    uint8_t* __buff = m_imp->m_client->GetBuffer(__size);
    if (__buff == NULL) {
        return ::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY;
    }

    if (!request.SerializeToArray(__buff, __size)) {
        return ::pebble::kRPC_ENCODE_FAILED;
    }

    if (m_imp->m_channel_name.empty()) {
        ::pebble::OnRpcResponse on_rsp = cxx::bind(&rpcMsgClientImp::recv_add_parallel, m_imp,
            cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3, ret_code, response);
        m_imp->m_client->SendRequestParallel(m_imp->GetHandle(), __head, __buff, __size, on_rsp, m_imp->m_methods["add"], ret_code, num_called, num_parallel);
    } else {
        *ret_code = m_imp->m_client->BroadcastRequest(m_imp->m_channel_name, __head, __buff, __size);
        --(*num_called);
        --(*num_parallel);
    }

    return *ret_code;
}

void rpcMsgClient::add(const ::example::CalRequest& request, const cxx::function<void(int32_t ret_code, const ::example::CalResponse& response)>& cb) {
    ::pebble::RpcHead __head;
    __head.m_function_name.assign("rpcMsg:add");
    __head.m_message_type = ::pebble::kRPC_CALL;
    __head.m_session_id = m_imp->m_client->GenSessionId();

    int __size = request.ByteSize();
    uint8_t* __buff = m_imp->m_client->GetBuffer(__size);
    if (__buff == NULL) {
        ::example::CalResponse __response;
        cb(::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY, __response);
        return;
    }

    if (!request.SerializeToArray(__buff, __size)) {
        ::example::CalResponse __response;
        cb(::pebble::kRPC_ENCODE_FAILED, __response);
        return;
    }

    if (m_imp->m_channel_name.empty()) {
        ::pebble::OnRpcResponse on_rsp = cxx::bind(&rpcMsgClientImp::recv_add, m_imp,
            cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3, cb);
        int32_t __ret = m_imp->m_client->SendRequest(m_imp->GetHandle(), __head, __buff, __size, on_rsp, m_imp->m_methods["add"]);
        if (__ret != ::pebble::kRPC_SUCCESS) {
            ::example::CalResponse __response;
            cb(__ret, __response);
            return;
        }
    } else {
        int32_t __ret = m_imp->m_client->BroadcastRequest(m_imp->m_channel_name, __head, __buff, __size);
        if (__ret != ::pebble::kRPC_SUCCESS) {
            ::example::CalResponse __response;
            cb(__ret, __response);
            return;
        }
    }

}

int32_t rpcMsgClient::login(const ::example::LoginInfo& request, ::example::playersInfo* response) {
    ::pebble::RpcHead __head;
    __head.m_function_name.assign("rpcMsg:login");
    __head.m_message_type = ::pebble::kRPC_CALL;
    __head.m_session_id = m_imp->m_client->GenSessionId();

    int __size = request.ByteSize();
    uint8_t* __buff = m_imp->m_client->GetBuffer(__size);
    if (__buff == NULL) {
        return ::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY;
    }

    if (!request.SerializeToArray(__buff, __size)) {
        return ::pebble::kRPC_ENCODE_FAILED;
    }

    if (m_imp->m_channel_name.empty()) {
        ::pebble::OnRpcResponse on_rsp = cxx::bind(&rpcMsgClientImp::recv_login_sync, m_imp,
            cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3, response);
        return m_imp->m_client->SendRequestSync(m_imp->GetHandle(), __head, __buff, __size, on_rsp, m_imp->m_methods["login"]);
    } else {
        return m_imp->m_client->BroadcastRequest(m_imp->m_channel_name, __head, __buff, __size);
    }

}

int32_t rpcMsgClient::Parallellogin(const ::example::LoginInfo& request, int32_t* ret_code, ::example::playersInfo* response, uint32_t* num_called, uint32_t* num_parallel) {
    ::pebble::RpcHead __head;
    __head.m_function_name.assign("rpcMsg:login");
    __head.m_message_type = ::pebble::kRPC_CALL;
    __head.m_session_id = m_imp->m_client->GenSessionId();

    int __size = request.ByteSize();
    uint8_t* __buff = m_imp->m_client->GetBuffer(__size);
    if (__buff == NULL) {
        return ::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY;
    }

    if (!request.SerializeToArray(__buff, __size)) {
        return ::pebble::kRPC_ENCODE_FAILED;
    }

    if (m_imp->m_channel_name.empty()) {
        ::pebble::OnRpcResponse on_rsp = cxx::bind(&rpcMsgClientImp::recv_login_parallel, m_imp,
            cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3, ret_code, response);
        m_imp->m_client->SendRequestParallel(m_imp->GetHandle(), __head, __buff, __size, on_rsp, m_imp->m_methods["login"], ret_code, num_called, num_parallel);
    } else {
        *ret_code = m_imp->m_client->BroadcastRequest(m_imp->m_channel_name, __head, __buff, __size);
        --(*num_called);
        --(*num_parallel);
    }

    return *ret_code;
}

void rpcMsgClient::login(const ::example::LoginInfo& request, const cxx::function<void(int32_t ret_code, const ::example::playersInfo& response)>& cb) {
    ::pebble::RpcHead __head;
    __head.m_function_name.assign("rpcMsg:login");
    __head.m_message_type = ::pebble::kRPC_CALL;
    __head.m_session_id = m_imp->m_client->GenSessionId();

    int __size = request.ByteSize();
    uint8_t* __buff = m_imp->m_client->GetBuffer(__size);
    if (__buff == NULL) {
        ::example::playersInfo __response;
        cb(::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY, __response);
        return;
    }

    if (!request.SerializeToArray(__buff, __size)) {
        ::example::playersInfo __response;
        cb(::pebble::kRPC_ENCODE_FAILED, __response);
        return;
    }

    if (m_imp->m_channel_name.empty()) {
        ::pebble::OnRpcResponse on_rsp = cxx::bind(&rpcMsgClientImp::recv_login, m_imp,
            cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3, cb);
        int32_t __ret = m_imp->m_client->SendRequest(m_imp->GetHandle(), __head, __buff, __size, on_rsp, m_imp->m_methods["login"]);
        if (__ret != ::pebble::kRPC_SUCCESS) {
            ::example::playersInfo __response;
            cb(__ret, __response);
            return;
        }
    } else {
        int32_t __ret = m_imp->m_client->BroadcastRequest(m_imp->m_channel_name, __head, __buff, __size);
        if (__ret != ::pebble::kRPC_SUCCESS) {
            ::example::playersInfo __response;
            cb(__ret, __response);
            return;
        }
    }

}

int32_t rpcMsgClient::modifyStatus(const ::example::StatusReceive& request, ::example::commonResponse* response) {
    ::pebble::RpcHead __head;
    __head.m_function_name.assign("rpcMsg:modifyStatus");
    __head.m_message_type = ::pebble::kRPC_CALL;
    __head.m_session_id = m_imp->m_client->GenSessionId();

    int __size = request.ByteSize();
    uint8_t* __buff = m_imp->m_client->GetBuffer(__size);
    if (__buff == NULL) {
        return ::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY;
    }

    if (!request.SerializeToArray(__buff, __size)) {
        return ::pebble::kRPC_ENCODE_FAILED;
    }

    if (m_imp->m_channel_name.empty()) {
        ::pebble::OnRpcResponse on_rsp = cxx::bind(&rpcMsgClientImp::recv_modifyStatus_sync, m_imp,
            cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3, response);
        return m_imp->m_client->SendRequestSync(m_imp->GetHandle(), __head, __buff, __size, on_rsp, m_imp->m_methods["modifyStatus"]);
    } else {
        return m_imp->m_client->BroadcastRequest(m_imp->m_channel_name, __head, __buff, __size);
    }

}

int32_t rpcMsgClient::ParallelmodifyStatus(const ::example::StatusReceive& request, int32_t* ret_code, ::example::commonResponse* response, uint32_t* num_called, uint32_t* num_parallel) {
    ::pebble::RpcHead __head;
    __head.m_function_name.assign("rpcMsg:modifyStatus");
    __head.m_message_type = ::pebble::kRPC_CALL;
    __head.m_session_id = m_imp->m_client->GenSessionId();

    int __size = request.ByteSize();
    uint8_t* __buff = m_imp->m_client->GetBuffer(__size);
    if (__buff == NULL) {
        return ::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY;
    }

    if (!request.SerializeToArray(__buff, __size)) {
        return ::pebble::kRPC_ENCODE_FAILED;
    }

    if (m_imp->m_channel_name.empty()) {
        ::pebble::OnRpcResponse on_rsp = cxx::bind(&rpcMsgClientImp::recv_modifyStatus_parallel, m_imp,
            cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3, ret_code, response);
        m_imp->m_client->SendRequestParallel(m_imp->GetHandle(), __head, __buff, __size, on_rsp, m_imp->m_methods["modifyStatus"], ret_code, num_called, num_parallel);
    } else {
        *ret_code = m_imp->m_client->BroadcastRequest(m_imp->m_channel_name, __head, __buff, __size);
        --(*num_called);
        --(*num_parallel);
    }

    return *ret_code;
}

void rpcMsgClient::modifyStatus(const ::example::StatusReceive& request, const cxx::function<void(int32_t ret_code, const ::example::commonResponse& response)>& cb) {
    ::pebble::RpcHead __head;
    __head.m_function_name.assign("rpcMsg:modifyStatus");
    __head.m_message_type = ::pebble::kRPC_CALL;
    __head.m_session_id = m_imp->m_client->GenSessionId();

    int __size = request.ByteSize();
    uint8_t* __buff = m_imp->m_client->GetBuffer(__size);
    if (__buff == NULL) {
        ::example::commonResponse __response;
        cb(::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY, __response);
        return;
    }

    if (!request.SerializeToArray(__buff, __size)) {
        ::example::commonResponse __response;
        cb(::pebble::kRPC_ENCODE_FAILED, __response);
        return;
    }

    if (m_imp->m_channel_name.empty()) {
        ::pebble::OnRpcResponse on_rsp = cxx::bind(&rpcMsgClientImp::recv_modifyStatus, m_imp,
            cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3, cb);
        int32_t __ret = m_imp->m_client->SendRequest(m_imp->GetHandle(), __head, __buff, __size, on_rsp, m_imp->m_methods["modifyStatus"]);
        if (__ret != ::pebble::kRPC_SUCCESS) {
            ::example::commonResponse __response;
            cb(__ret, __response);
            return;
        }
    } else {
        int32_t __ret = m_imp->m_client->BroadcastRequest(m_imp->m_channel_name, __head, __buff, __size);
        if (__ret != ::pebble::kRPC_SUCCESS) {
            ::example::commonResponse __response;
            cb(__ret, __response);
            return;
        }
    }

}

int32_t rpcMsgClient::move(const ::example::moveRequest& request, ::example::commonResponse* response) {
    ::pebble::RpcHead __head;
    __head.m_function_name.assign("rpcMsg:move");
    __head.m_message_type = ::pebble::kRPC_CALL;
    __head.m_session_id = m_imp->m_client->GenSessionId();

    int __size = request.ByteSize();
    uint8_t* __buff = m_imp->m_client->GetBuffer(__size);
    if (__buff == NULL) {
        return ::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY;
    }

    if (!request.SerializeToArray(__buff, __size)) {
        return ::pebble::kRPC_ENCODE_FAILED;
    }

    if (m_imp->m_channel_name.empty()) {
        ::pebble::OnRpcResponse on_rsp = cxx::bind(&rpcMsgClientImp::recv_move_sync, m_imp,
            cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3, response);
        return m_imp->m_client->SendRequestSync(m_imp->GetHandle(), __head, __buff, __size, on_rsp, m_imp->m_methods["move"]);
    } else {
        return m_imp->m_client->BroadcastRequest(m_imp->m_channel_name, __head, __buff, __size);
    }

}

int32_t rpcMsgClient::Parallelmove(const ::example::moveRequest& request, int32_t* ret_code, ::example::commonResponse* response, uint32_t* num_called, uint32_t* num_parallel) {
    ::pebble::RpcHead __head;
    __head.m_function_name.assign("rpcMsg:move");
    __head.m_message_type = ::pebble::kRPC_CALL;
    __head.m_session_id = m_imp->m_client->GenSessionId();

    int __size = request.ByteSize();
    uint8_t* __buff = m_imp->m_client->GetBuffer(__size);
    if (__buff == NULL) {
        return ::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY;
    }

    if (!request.SerializeToArray(__buff, __size)) {
        return ::pebble::kRPC_ENCODE_FAILED;
    }

    if (m_imp->m_channel_name.empty()) {
        ::pebble::OnRpcResponse on_rsp = cxx::bind(&rpcMsgClientImp::recv_move_parallel, m_imp,
            cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3, ret_code, response);
        m_imp->m_client->SendRequestParallel(m_imp->GetHandle(), __head, __buff, __size, on_rsp, m_imp->m_methods["move"], ret_code, num_called, num_parallel);
    } else {
        *ret_code = m_imp->m_client->BroadcastRequest(m_imp->m_channel_name, __head, __buff, __size);
        --(*num_called);
        --(*num_parallel);
    }

    return *ret_code;
}

void rpcMsgClient::move(const ::example::moveRequest& request, const cxx::function<void(int32_t ret_code, const ::example::commonResponse& response)>& cb) {
    ::pebble::RpcHead __head;
    __head.m_function_name.assign("rpcMsg:move");
    __head.m_message_type = ::pebble::kRPC_CALL;
    __head.m_session_id = m_imp->m_client->GenSessionId();

    int __size = request.ByteSize();
    uint8_t* __buff = m_imp->m_client->GetBuffer(__size);
    if (__buff == NULL) {
        ::example::commonResponse __response;
        cb(::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY, __response);
        return;
    }

    if (!request.SerializeToArray(__buff, __size)) {
        ::example::commonResponse __response;
        cb(::pebble::kRPC_ENCODE_FAILED, __response);
        return;
    }

    if (m_imp->m_channel_name.empty()) {
        ::pebble::OnRpcResponse on_rsp = cxx::bind(&rpcMsgClientImp::recv_move, m_imp,
            cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3, cb);
        int32_t __ret = m_imp->m_client->SendRequest(m_imp->GetHandle(), __head, __buff, __size, on_rsp, m_imp->m_methods["move"]);
        if (__ret != ::pebble::kRPC_SUCCESS) {
            ::example::commonResponse __response;
            cb(__ret, __response);
            return;
        }
    } else {
        int32_t __ret = m_imp->m_client->BroadcastRequest(m_imp->m_channel_name, __head, __buff, __size);
        if (__ret != ::pebble::kRPC_SUCCESS) {
            ::example::commonResponse __response;
            cb(__ret, __response);
            return;
        }
    }

}

int32_t rpcMsgClient::chat(const ::example::chatReceive& request, ::example::commonResponse* response) {
    ::pebble::RpcHead __head;
    __head.m_function_name.assign("rpcMsg:chat");
    __head.m_message_type = ::pebble::kRPC_CALL;
    __head.m_session_id = m_imp->m_client->GenSessionId();

    int __size = request.ByteSize();
    uint8_t* __buff = m_imp->m_client->GetBuffer(__size);
    if (__buff == NULL) {
        return ::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY;
    }

    if (!request.SerializeToArray(__buff, __size)) {
        return ::pebble::kRPC_ENCODE_FAILED;
    }

    if (m_imp->m_channel_name.empty()) {
        ::pebble::OnRpcResponse on_rsp = cxx::bind(&rpcMsgClientImp::recv_chat_sync, m_imp,
            cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3, response);
        return m_imp->m_client->SendRequestSync(m_imp->GetHandle(), __head, __buff, __size, on_rsp, m_imp->m_methods["chat"]);
    } else {
        return m_imp->m_client->BroadcastRequest(m_imp->m_channel_name, __head, __buff, __size);
    }

}

int32_t rpcMsgClient::Parallelchat(const ::example::chatReceive& request, int32_t* ret_code, ::example::commonResponse* response, uint32_t* num_called, uint32_t* num_parallel) {
    ::pebble::RpcHead __head;
    __head.m_function_name.assign("rpcMsg:chat");
    __head.m_message_type = ::pebble::kRPC_CALL;
    __head.m_session_id = m_imp->m_client->GenSessionId();

    int __size = request.ByteSize();
    uint8_t* __buff = m_imp->m_client->GetBuffer(__size);
    if (__buff == NULL) {
        return ::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY;
    }

    if (!request.SerializeToArray(__buff, __size)) {
        return ::pebble::kRPC_ENCODE_FAILED;
    }

    if (m_imp->m_channel_name.empty()) {
        ::pebble::OnRpcResponse on_rsp = cxx::bind(&rpcMsgClientImp::recv_chat_parallel, m_imp,
            cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3, ret_code, response);
        m_imp->m_client->SendRequestParallel(m_imp->GetHandle(), __head, __buff, __size, on_rsp, m_imp->m_methods["chat"], ret_code, num_called, num_parallel);
    } else {
        *ret_code = m_imp->m_client->BroadcastRequest(m_imp->m_channel_name, __head, __buff, __size);
        --(*num_called);
        --(*num_parallel);
    }

    return *ret_code;
}

void rpcMsgClient::chat(const ::example::chatReceive& request, const cxx::function<void(int32_t ret_code, const ::example::commonResponse& response)>& cb) {
    ::pebble::RpcHead __head;
    __head.m_function_name.assign("rpcMsg:chat");
    __head.m_message_type = ::pebble::kRPC_CALL;
    __head.m_session_id = m_imp->m_client->GenSessionId();

    int __size = request.ByteSize();
    uint8_t* __buff = m_imp->m_client->GetBuffer(__size);
    if (__buff == NULL) {
        ::example::commonResponse __response;
        cb(::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY, __response);
        return;
    }

    if (!request.SerializeToArray(__buff, __size)) {
        ::example::commonResponse __response;
        cb(::pebble::kRPC_ENCODE_FAILED, __response);
        return;
    }

    if (m_imp->m_channel_name.empty()) {
        ::pebble::OnRpcResponse on_rsp = cxx::bind(&rpcMsgClientImp::recv_chat, m_imp,
            cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3, cb);
        int32_t __ret = m_imp->m_client->SendRequest(m_imp->GetHandle(), __head, __buff, __size, on_rsp, m_imp->m_methods["chat"]);
        if (__ret != ::pebble::kRPC_SUCCESS) {
            ::example::commonResponse __response;
            cb(__ret, __response);
            return;
        }
    } else {
        int32_t __ret = m_imp->m_client->BroadcastRequest(m_imp->m_channel_name, __head, __buff, __size);
        if (__ret != ::pebble::kRPC_SUCCESS) {
            ::example::commonResponse __response;
            cb(__ret, __response);
            return;
        }
    }

}

rpcMsgClientImp::rpcMsgClientImp(::pebble::PebbleRpc* rpc) {
    m_client    = rpc;
    m_route_key = 0;
    m_methods["add"] = 10000;
    m_methods["login"] = 10000;
    m_methods["modifyStatus"] = 10000;
    m_methods["move"] = 10000;
    m_methods["chat"] = 10000;
}

rpcMsgClientImp::~rpcMsgClientImp() {}

int64_t rpcMsgClientImp::GetHandle() {
    if (m_route_func) {
        return m_route_func(m_route_key);
    }

    return m_handle;
}

int32_t rpcMsgClientImp::recv_add_sync(int32_t ret, const uint8_t* buff, uint32_t buff_len, ::example::CalResponse* response) {
    if (ret != ::pebble::kRPC_SUCCESS) {
        if (0 == buff_len) {
            return ret;
        }
    }

    if (!response->ParseFromArray((const void*)buff, buff_len)) {
        return ::pebble::kRPC_DECODE_FAILED;
    }

    return ret != ::pebble::kRPC_SUCCESS ? ret : ::pebble::kRPC_SUCCESS;
}

int32_t rpcMsgClientImp::recv_add_parallel(int32_t ret, const uint8_t* buff, uint32_t buff_len, int32_t* ret_code, ::example::CalResponse* response) {
    *ret_code = recv_add_sync(ret, buff, buff_len, response);
    return *ret_code;
}

int32_t rpcMsgClientImp::recv_add(int32_t ret, const uint8_t* buff, uint32_t buff_len, cxx::function<void(int ret_code, const ::example::CalResponse& response)>& cb) {
    ::example::CalResponse __response;
    if (ret != ::pebble::kRPC_SUCCESS) {
        if (0 == buff_len) {
            cb(ret, __response);
            return ret;
        }
    }
    if (!__response.ParseFromArray((const void*)buff, buff_len)) {
        cb(::pebble::kRPC_DECODE_FAILED, __response);
        return ::pebble::kRPC_DECODE_FAILED;
    }
    cb(ret != ::pebble::kRPC_SUCCESS ? ret : ::pebble::kRPC_SUCCESS, __response);
    return ret != ::pebble::kRPC_SUCCESS ? ret : ::pebble::kRPC_SUCCESS;
}

int32_t rpcMsgClientImp::recv_login_sync(int32_t ret, const uint8_t* buff, uint32_t buff_len, ::example::playersInfo* response) {
    if (ret != ::pebble::kRPC_SUCCESS) {
        if (0 == buff_len) {
            return ret;
        }
    }

    if (!response->ParseFromArray((const void*)buff, buff_len)) {
        return ::pebble::kRPC_DECODE_FAILED;
    }

    return ret != ::pebble::kRPC_SUCCESS ? ret : ::pebble::kRPC_SUCCESS;
}

int32_t rpcMsgClientImp::recv_login_parallel(int32_t ret, const uint8_t* buff, uint32_t buff_len, int32_t* ret_code, ::example::playersInfo* response) {
    *ret_code = recv_login_sync(ret, buff, buff_len, response);
    return *ret_code;
}

int32_t rpcMsgClientImp::recv_login(int32_t ret, const uint8_t* buff, uint32_t buff_len, cxx::function<void(int ret_code, const ::example::playersInfo& response)>& cb) {
    ::example::playersInfo __response;
    if (ret != ::pebble::kRPC_SUCCESS) {
        if (0 == buff_len) {
            cb(ret, __response);
            return ret;
        }
    }
    if (!__response.ParseFromArray((const void*)buff, buff_len)) {
        cb(::pebble::kRPC_DECODE_FAILED, __response);
        return ::pebble::kRPC_DECODE_FAILED;
    }
    cb(ret != ::pebble::kRPC_SUCCESS ? ret : ::pebble::kRPC_SUCCESS, __response);
    return ret != ::pebble::kRPC_SUCCESS ? ret : ::pebble::kRPC_SUCCESS;
}

int32_t rpcMsgClientImp::recv_modifyStatus_sync(int32_t ret, const uint8_t* buff, uint32_t buff_len, ::example::commonResponse* response) {
    if (ret != ::pebble::kRPC_SUCCESS) {
        if (0 == buff_len) {
            return ret;
        }
    }

    if (!response->ParseFromArray((const void*)buff, buff_len)) {
        return ::pebble::kRPC_DECODE_FAILED;
    }

    return ret != ::pebble::kRPC_SUCCESS ? ret : ::pebble::kRPC_SUCCESS;
}

int32_t rpcMsgClientImp::recv_modifyStatus_parallel(int32_t ret, const uint8_t* buff, uint32_t buff_len, int32_t* ret_code, ::example::commonResponse* response) {
    *ret_code = recv_modifyStatus_sync(ret, buff, buff_len, response);
    return *ret_code;
}

int32_t rpcMsgClientImp::recv_modifyStatus(int32_t ret, const uint8_t* buff, uint32_t buff_len, cxx::function<void(int ret_code, const ::example::commonResponse& response)>& cb) {
    ::example::commonResponse __response;
    if (ret != ::pebble::kRPC_SUCCESS) {
        if (0 == buff_len) {
            cb(ret, __response);
            return ret;
        }
    }
    if (!__response.ParseFromArray((const void*)buff, buff_len)) {
        cb(::pebble::kRPC_DECODE_FAILED, __response);
        return ::pebble::kRPC_DECODE_FAILED;
    }
    cb(ret != ::pebble::kRPC_SUCCESS ? ret : ::pebble::kRPC_SUCCESS, __response);
    return ret != ::pebble::kRPC_SUCCESS ? ret : ::pebble::kRPC_SUCCESS;
}

int32_t rpcMsgClientImp::recv_move_sync(int32_t ret, const uint8_t* buff, uint32_t buff_len, ::example::commonResponse* response) {
    if (ret != ::pebble::kRPC_SUCCESS) {
        if (0 == buff_len) {
            return ret;
        }
    }

    if (!response->ParseFromArray((const void*)buff, buff_len)) {
        return ::pebble::kRPC_DECODE_FAILED;
    }

    return ret != ::pebble::kRPC_SUCCESS ? ret : ::pebble::kRPC_SUCCESS;
}

int32_t rpcMsgClientImp::recv_move_parallel(int32_t ret, const uint8_t* buff, uint32_t buff_len, int32_t* ret_code, ::example::commonResponse* response) {
    *ret_code = recv_move_sync(ret, buff, buff_len, response);
    return *ret_code;
}

int32_t rpcMsgClientImp::recv_move(int32_t ret, const uint8_t* buff, uint32_t buff_len, cxx::function<void(int ret_code, const ::example::commonResponse& response)>& cb) {
    ::example::commonResponse __response;
    if (ret != ::pebble::kRPC_SUCCESS) {
        if (0 == buff_len) {
            cb(ret, __response);
            return ret;
        }
    }
    if (!__response.ParseFromArray((const void*)buff, buff_len)) {
        cb(::pebble::kRPC_DECODE_FAILED, __response);
        return ::pebble::kRPC_DECODE_FAILED;
    }
    cb(ret != ::pebble::kRPC_SUCCESS ? ret : ::pebble::kRPC_SUCCESS, __response);
    return ret != ::pebble::kRPC_SUCCESS ? ret : ::pebble::kRPC_SUCCESS;
}

int32_t rpcMsgClientImp::recv_chat_sync(int32_t ret, const uint8_t* buff, uint32_t buff_len, ::example::commonResponse* response) {
    if (ret != ::pebble::kRPC_SUCCESS) {
        if (0 == buff_len) {
            return ret;
        }
    }

    if (!response->ParseFromArray((const void*)buff, buff_len)) {
        return ::pebble::kRPC_DECODE_FAILED;
    }

    return ret != ::pebble::kRPC_SUCCESS ? ret : ::pebble::kRPC_SUCCESS;
}

int32_t rpcMsgClientImp::recv_chat_parallel(int32_t ret, const uint8_t* buff, uint32_t buff_len, int32_t* ret_code, ::example::commonResponse* response) {
    *ret_code = recv_chat_sync(ret, buff, buff_len, response);
    return *ret_code;
}

int32_t rpcMsgClientImp::recv_chat(int32_t ret, const uint8_t* buff, uint32_t buff_len, cxx::function<void(int ret_code, const ::example::commonResponse& response)>& cb) {
    ::example::commonResponse __response;
    if (ret != ::pebble::kRPC_SUCCESS) {
        if (0 == buff_len) {
            cb(ret, __response);
            return ret;
        }
    }
    if (!__response.ParseFromArray((const void*)buff, buff_len)) {
        cb(::pebble::kRPC_DECODE_FAILED, __response);
        return ::pebble::kRPC_DECODE_FAILED;
    }
    cb(ret != ::pebble::kRPC_SUCCESS ? ret : ::pebble::kRPC_SUCCESS, __response);
    return ret != ::pebble::kRPC_SUCCESS ? ret : ::pebble::kRPC_SUCCESS;
}

__rpcMsgSkeleton::__rpcMsgSkeleton(::pebble::PebbleRpc* server, rpcMsgServerInterface* iface) {
    m_server = server;
    m_iface  = iface;
}

int32_t __rpcMsgSkeleton::RegisterServiceFunction() {
    if (!m_server) {
        return ::pebble::kRPC_INVALID_PARAM;
    }

    ::pebble::OnRpcRequest cb;
    int32_t ret = ::pebble::kRPC_SUCCESS;

    cb = cxx::bind(&__rpcMsgSkeleton::process_add, this,
        cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3);
    ret = m_server->AddOnRequestFunction("rpcMsg:add", cb);
    if (ret != ::pebble::kRPC_SUCCESS) {
        return ret;
    }

    cb = cxx::bind(&__rpcMsgSkeleton::process_login, this,
        cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3);
    ret = m_server->AddOnRequestFunction("rpcMsg:login", cb);
    if (ret != ::pebble::kRPC_SUCCESS) {
        return ret;
    }

    cb = cxx::bind(&__rpcMsgSkeleton::process_modifyStatus, this,
        cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3);
    ret = m_server->AddOnRequestFunction("rpcMsg:modifyStatus", cb);
    if (ret != ::pebble::kRPC_SUCCESS) {
        return ret;
    }

    cb = cxx::bind(&__rpcMsgSkeleton::process_move, this,
        cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3);
    ret = m_server->AddOnRequestFunction("rpcMsg:move", cb);
    if (ret != ::pebble::kRPC_SUCCESS) {
        return ret;
    }

    cb = cxx::bind(&__rpcMsgSkeleton::process_chat, this,
        cxx::placeholders::_1, cxx::placeholders::_2, cxx::placeholders::_3);
    ret = m_server->AddOnRequestFunction("rpcMsg:chat", cb);
    if (ret != ::pebble::kRPC_SUCCESS) {
        return ret;
    }

    return ret;
}

int32_t __rpcMsgSkeleton::process_add(const uint8_t* buff, uint32_t buff_len, cxx::function<int32_t(int32_t ret, const uint8_t* buff, uint32_t buff_len)>& rsp) {
    ::example::CalRequest __request;
    if (!__request.ParseFromArray((const void*)buff, buff_len)) {
        rsp(::pebble::kPEBBLE_RPC_DECODE_BODY_FAILED, NULL, 0);
        return ::pebble::kPEBBLE_RPC_DECODE_BODY_FAILED;
    }

    cxx::function<void(int32_t ret_code, const ::example::CalResponse& response)> __rsp =
        cxx::bind(&__rpcMsgSkeleton::return_add, this,
            rsp, cxx::placeholders::_1, cxx::placeholders::_2);

    m_iface->add(__request, __rsp);

    return ::pebble::kRPC_SUCCESS;
}

void __rpcMsgSkeleton::return_add(cxx::function<int32_t(int32_t ret, const uint8_t* buff, uint32_t buff_len)>& rsp, int32_t ret_code, const ::example::CalResponse& response) {
    int __size = response.ByteSize();
    uint8_t* __buff = m_server->GetBuffer(__size);
    if (__buff == NULL) {
        rsp(::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY, NULL, 0);
        return;
    }

    if (!response.SerializeToArray(__buff, __size)) {
        rsp(::pebble::kPEBBLE_RPC_ENCODE_BODY_FAILED, NULL, 0);
        return;
    }

    rsp(ret_code, __buff, __size);
}

int32_t __rpcMsgSkeleton::process_login(const uint8_t* buff, uint32_t buff_len, cxx::function<int32_t(int32_t ret, const uint8_t* buff, uint32_t buff_len)>& rsp) {
    ::example::LoginInfo __request;
    if (!__request.ParseFromArray((const void*)buff, buff_len)) {
        rsp(::pebble::kPEBBLE_RPC_DECODE_BODY_FAILED, NULL, 0);
        return ::pebble::kPEBBLE_RPC_DECODE_BODY_FAILED;
    }

    cxx::function<void(int32_t ret_code, const ::example::playersInfo& response)> __rsp =
        cxx::bind(&__rpcMsgSkeleton::return_login, this,
            rsp, cxx::placeholders::_1, cxx::placeholders::_2);

    m_iface->login(__request, __rsp);

    return ::pebble::kRPC_SUCCESS;
}

void __rpcMsgSkeleton::return_login(cxx::function<int32_t(int32_t ret, const uint8_t* buff, uint32_t buff_len)>& rsp, int32_t ret_code, const ::example::playersInfo& response) {
    int __size = response.ByteSize();
    uint8_t* __buff = m_server->GetBuffer(__size);
    if (__buff == NULL) {
        rsp(::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY, NULL, 0);
        return;
    }

    if (!response.SerializeToArray(__buff, __size)) {
        rsp(::pebble::kPEBBLE_RPC_ENCODE_BODY_FAILED, NULL, 0);
        return;
    }

    rsp(ret_code, __buff, __size);
}

int32_t __rpcMsgSkeleton::process_modifyStatus(const uint8_t* buff, uint32_t buff_len, cxx::function<int32_t(int32_t ret, const uint8_t* buff, uint32_t buff_len)>& rsp) {
    ::example::StatusReceive __request;
    if (!__request.ParseFromArray((const void*)buff, buff_len)) {
        rsp(::pebble::kPEBBLE_RPC_DECODE_BODY_FAILED, NULL, 0);
        return ::pebble::kPEBBLE_RPC_DECODE_BODY_FAILED;
    }

    cxx::function<void(int32_t ret_code, const ::example::commonResponse& response)> __rsp =
        cxx::bind(&__rpcMsgSkeleton::return_modifyStatus, this,
            rsp, cxx::placeholders::_1, cxx::placeholders::_2);

    m_iface->modifyStatus(__request, __rsp);

    return ::pebble::kRPC_SUCCESS;
}

void __rpcMsgSkeleton::return_modifyStatus(cxx::function<int32_t(int32_t ret, const uint8_t* buff, uint32_t buff_len)>& rsp, int32_t ret_code, const ::example::commonResponse& response) {
    int __size = response.ByteSize();
    uint8_t* __buff = m_server->GetBuffer(__size);
    if (__buff == NULL) {
        rsp(::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY, NULL, 0);
        return;
    }

    if (!response.SerializeToArray(__buff, __size)) {
        rsp(::pebble::kPEBBLE_RPC_ENCODE_BODY_FAILED, NULL, 0);
        return;
    }

    rsp(ret_code, __buff, __size);
}

int32_t __rpcMsgSkeleton::process_move(const uint8_t* buff, uint32_t buff_len, cxx::function<int32_t(int32_t ret, const uint8_t* buff, uint32_t buff_len)>& rsp) {
    ::example::moveRequest __request;
    if (!__request.ParseFromArray((const void*)buff, buff_len)) {
        rsp(::pebble::kPEBBLE_RPC_DECODE_BODY_FAILED, NULL, 0);
        return ::pebble::kPEBBLE_RPC_DECODE_BODY_FAILED;
    }

    cxx::function<void(int32_t ret_code, const ::example::commonResponse& response)> __rsp =
        cxx::bind(&__rpcMsgSkeleton::return_move, this,
            rsp, cxx::placeholders::_1, cxx::placeholders::_2);

    m_iface->move(__request, __rsp);

    return ::pebble::kRPC_SUCCESS;
}

void __rpcMsgSkeleton::return_move(cxx::function<int32_t(int32_t ret, const uint8_t* buff, uint32_t buff_len)>& rsp, int32_t ret_code, const ::example::commonResponse& response) {
    int __size = response.ByteSize();
    uint8_t* __buff = m_server->GetBuffer(__size);
    if (__buff == NULL) {
        rsp(::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY, NULL, 0);
        return;
    }

    if (!response.SerializeToArray(__buff, __size)) {
        rsp(::pebble::kPEBBLE_RPC_ENCODE_BODY_FAILED, NULL, 0);
        return;
    }

    rsp(ret_code, __buff, __size);
}

int32_t __rpcMsgSkeleton::process_chat(const uint8_t* buff, uint32_t buff_len, cxx::function<int32_t(int32_t ret, const uint8_t* buff, uint32_t buff_len)>& rsp) {
    ::example::chatReceive __request;
    if (!__request.ParseFromArray((const void*)buff, buff_len)) {
        rsp(::pebble::kPEBBLE_RPC_DECODE_BODY_FAILED, NULL, 0);
        return ::pebble::kPEBBLE_RPC_DECODE_BODY_FAILED;
    }

    cxx::function<void(int32_t ret_code, const ::example::commonResponse& response)> __rsp =
        cxx::bind(&__rpcMsgSkeleton::return_chat, this,
            rsp, cxx::placeholders::_1, cxx::placeholders::_2);

    m_iface->chat(__request, __rsp);

    return ::pebble::kRPC_SUCCESS;
}

void __rpcMsgSkeleton::return_chat(cxx::function<int32_t(int32_t ret, const uint8_t* buff, uint32_t buff_len)>& rsp, int32_t ret_code, const ::example::commonResponse& response) {
    int __size = response.ByteSize();
    uint8_t* __buff = m_server->GetBuffer(__size);
    if (__buff == NULL) {
        rsp(::pebble::kPEBBLE_RPC_INSUFFICIENT_MEMORY, NULL, 0);
        return;
    }

    if (!response.SerializeToArray(__buff, __size)) {
        rsp(::pebble::kPEBBLE_RPC_ENCODE_BODY_FAILED, NULL, 0);
        return;
    }

    rsp(ret_code, __buff, __size);
}


} // namespace example

