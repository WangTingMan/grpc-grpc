﻿#include <windows.h>

#pragma comment(lib,"libgrpc++_base.lib")
#pragma comment(lib,"libgrpc_transport_chttp2_client_insecure.lib")
#pragma comment(lib,"libgrpc_base_c.lib")
#pragma comment(lib,"gpr_base.lib")
#pragma comment(lib,"libgrpc.lib")
#pragma comment(lib,"libgrpc_secure.lib")
#pragma comment(lib,"libgrpc_transport_chttp2_client_secure.lib")
#pragma comment(lib,"libalts_util.lib")
#pragma comment(lib,"libgrpc++_codegen_base_src.lib")
#pragma comment(lib,"libgrpc_transport_chttp2_server_insecure.lib")
#pragma comment(lib,"libgrpc_transport_chttp2.lib")
#pragma comment(lib,"libprotobuf-c-nano.lib")
#pragma comment(lib,"libgrpc_client_channel.lib")
#pragma comment(lib,"libgrpc_deadline_filter.lib")
#pragma comment(lib,"libtsi.lib")
#pragma comment(lib,"libalts_frame_protector.lib")
#pragma comment(lib,"libtsi_interface.lib")
#pragma comment(lib,"libgrpc_transport_chttp2_alpn.lib")
#pragma comment(lib,"libgrpc_workaround_cronet_compression_filter.lib")
#pragma comment(lib,"libgrpc_client_authority_filter.lib")
#pragma comment(lib,"libgrpc_message_size_filter.lib")
#pragma comment(lib,"libgrpc_max_age_filter.lib")
#pragma comment(lib,"libgrpc_lb_policy_round_robin.lib")
#pragma comment(lib,"libgrpc_lb_policy_pick_first.lib")
#pragma comment(lib,"libgrpc_transport_inproc.lib")
#pragma comment(lib,"libgrpc_resolver_sockaddr.lib")
#pragma comment(lib,"libgrpc_lb_policy_grpclb.lib")
#pragma comment(lib,"libgrpc_resolver_dns_native.lib")
#pragma comment(lib,"libgrpc_resolver_fake.lib")
#pragma comment(lib,"libgrpc_trace.lib")
#pragma comment(lib,"libgrpc_http_filters.lib")
#pragma comment(lib,"libgrpc_transport_chttp2_server_secure.lib")
#pragma comment(lib,"census.lib")
#pragma comment(lib,"libgrpc_base.lib")
#pragma comment(lib,"libgrpc_transport_chttp2_client_connector.lib")
#pragma comment(lib,"libgrpc_resolver_dns_ares.lib")
#pragma comment(lib,"libgrpc_server_backward_compatibility.lib")

#pragma comment(lib,"libssl.lib")
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"zlib.lib")

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

