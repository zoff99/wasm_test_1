
#include "sodium.h"
#include "sodium/crypto_pwhash_scryptsalsa208sha256.h"
#include "../toxcore/tox.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <ctype.h>

#include <unistd.h>
#include <stdio.h>

//#include <future>
//#include <thread>

#include <emscripten.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/websocket.h>
#include <emscripten/threading.h>
#include <emscripten/posix_socket.h>
static EMSCRIPTEN_WEBSOCKET_T bridgeSocket = 0;
#endif

#define nullptr NULL

void bin2upHex(const uint8_t *bin, uint32_t bin_size, char *hex, uint32_t hex_size)
{
    sodium_bin2hex(hex, hex_size, bin, bin_size);

    for (size_t i = 0; i < hex_size - 1; i++) {
        hex[i] = toupper(hex[i]);
    }
}

//float lerp(float a, float b, float t) {
//    return (1 - t) * a + t * b;
//}

int EMSCRIPTEN_KEEPALIVE wasmtoxversion() {
  return tox_version_patch();
}

int EMSCRIPTEN_KEEPALIVE wasm_new_message_id() {
    uint8_t msg_id[100];
    tox_messagev3_get_new_message_id((uint8_t *)msg_id);
}

int lookup_host(const char *host) {
  struct addrinfo hints, *res;
  int errcode;
  char addrstr[100];
  void *ptr;

  memset(&hints, 0, sizeof (hints));
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags |= AI_CANONNAME;

  errcode = getaddrinfo(host, NULL, &hints, &res);
  if (errcode != 0) {
    printf("getaddrinfo failed!\n");
    return -1;
  }

  printf("Host: %s\n", host);
  while (res) {
    inet_ntop(res->ai_family, res->ai_addr->sa_data, addrstr, 100);

    switch (res->ai_family) {
    case AF_INET:
      ptr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
      break;
    case AF_INET6:
      ptr = &((struct sockaddr_in6 *)res->ai_addr)->sin6_addr;
      break;
    }
    inet_ntop(res->ai_family, ptr, addrstr, 100);
    printf("IPv%d address: %s (%s)\n", res->ai_family == PF_INET6 ? 6 : 4, addrstr, res->ai_canonname);
    res = res->ai_next;
  }

  return 0;
}

//int main(int argc , char *argv[]) {
/*
emscripten_console_log("main start ...");

#ifdef __EMSCRIPTEN__
  bridgeSocket = emscripten_init_websocket_to_posix_socket_bridge("ws://localhost:8080");
  // Synchronously wait until connection has been established.
  uint16_t readyState = 0;
  do {
    emscripten_websocket_get_ready_state(bridgeSocket, &readyState);
    emscripten_thread_sleep(100);
  } while (readyState == 0);
#endif
*/
  // lookup_host("google.com");
  // emscripten_exit_with_live_runtime();
//}

//int main() {
//    emscripten_console_log("main start ...");
//    emscripten_exit_with_live_runtime();
//    return 0;
//}

struct Node1 {
    char *ip;
    char *key;
    uint16_t udp_port;
    uint16_t tcp_port;
} nodes1[] = {
{ "2604:a880:1:20::32f:1001", "BEF0CFB37AF874BD17B9A8F9FE64C75521DB95A37D33C5BDB00E9CF58659C04F", 33445, 33445 },
{ "46.101.197.175", "CD133B521159541FB1D326DE9850F5E56A6C724B5B8E5EB5CD8D950408E95707", 33445, 3389 },
{ "144.217.167.73","7E5668E0EE09E19F320AD47902419331FFEE147BB3606769CFBE921A2A2FD34C",33445,33445},
{ "tox1.mf-net.eu", "B3E5FA80DC8EBD1149AD2AB35ED8B85BD546DEDE261CA593234C619249419506", 33445, 3389 },
{ "bg.tox.dcntrlzd.network", "20AD2A54D70E827302CDF5F11D7C43FA0EC987042C36628E64B2B721A1426E36", 33445, 33445 },
{"91.219.59.156","8E7D0B859922EF569298B4D261A8CCB5FEA14FB91ED412A7603A585A25698832",33445,33445},
{"85.143.221.42","DA4E4ED4B697F2E9B000EEFE3A34B554ACD3F45F5C96EAEA2516DD7FF9AF7B43",33445,33445},
{"tox.initramfs.io","3F0A45A268367C1BEA652F258C85F4A66DA76BCAA667A49E770BCC4917AB6A25",33445,33445},
{"144.217.167.73","7E5668E0EE09E19F320AD47902419331FFEE147BB3606769CFBE921A2A2FD34C",33445,33445},
{"tox.abilinski.com","10C00EB250C3233E343E2AEBA07115A5C28920E9C8D29492F6D00B29049EDC7E",33445,33445},
{"tox.novg.net","D527E5847F8330D628DAB1814F0A422F6DC9D0A300E6C357634EE2DA88C35463",33445,33445},
{"198.199.98.108","BEF0CFB37AF874BD17B9A8F9FE64C75521DB95A37D33C5BDB00E9CF58659C04F",33445,33445},
{"tox.kurnevsky.net","82EF82BA33445A1F91A7DB27189ECFC0C013E06E3DA71F588ED692BED625EC23",33445,33445},
{"81.169.136.229","E0DB78116AC6500398DDBA2AEEF3220BB116384CAB714C5D1FCD61EA2B69D75E",33445,33445},
{"205.185.115.131","3091C6BEB2A993F1C6300C16549FABA67098FF3D62C6D253828B531470B53D68",53,53},
{"bg.tox.dcntrlzd.network","20AD2A54D70E827302CDF5F11D7C43FA0EC987042C36628E64B2B721A1426E36",33445,33445},
{"46.101.197.175","CD133B521159541FB1D326DE9850F5E56A6C724B5B8E5EB5CD8D950408E95707",33445,33445},
{"tox1.mf-net.eu","B3E5FA80DC8EBD1149AD2AB35ED8B85BD546DEDE261CA593234C619249419506",33445,33445},
{"tox2.mf-net.eu","70EA214FDE161E7432530605213F18F7427DC773E276B3E317A07531F548545F",33445,33445},
{"195.201.7.101","B84E865125B4EC4C368CD047C72BCE447644A2DC31EF75BD2CDA345BFD310107",33445,33445},
{"tox4.plastiras.org","836D1DA2BE12FE0E669334E437BE3FB02806F1528C2B2782113E0910C7711409",33445,33445},
{"gt.sot-te.ch","F4F4856F1A311049E0262E9E0A160610284B434F46299988A9CB42BD3D494618",33445,33445},
{"188.225.9.167","1911341A83E02503AB1FD6561BD64AF3A9D6C3F12B5FBB656976B2E678644A67",33445,33445},
{"122.116.39.151","5716530A10D362867C8E87EE1CD5362A233BAFBBA4CF47FA73B7CAD368BD5E6E",33445,33445},
{"195.123.208.139","534A589BA7427C631773D13083570F529238211893640C99D1507300F055FE73",33445,33445},
{"tox3.plastiras.org","4B031C96673B6FF123269FF18F2847E1909A8A04642BBECD0189AC8AEEADAF64",33445,33445},
{"104.225.141.59","933BA20B2E258B4C0D475B6DECE90C7E827FE83EFA9655414E7841251B19A72C",43334,43334},
{"139.162.110.188","F76A11284547163889DDC89A7738CF271797BF5E5E220643E97AD3C7E7903D55",33445,33445},
{"198.98.49.206","28DB44A3CEEE69146469855DFFE5F54DA567F5D65E03EFB1D38BBAEFF2553255",33445,33445},
{"172.105.109.31","D46E97CF995DC1820B92B7D899E152A217D36ABE22730FEA4B6BF1BFC06C617C",33445,33445},
{"ru.tox.dcntrlzd.network","DBB2E896990ECC383DA2E68A01CA148105E34F9B3B9356F2FE2B5096FDB62762",33445,33445},
{"91.146.66.26","B5E7DAC610DBDE55F359C7F8690B294C8E4FCEC4385DE9525DBFA5523EAD9D53",33445,33445},
{"tox01.ky0uraku.xyz","FD04EB03ABC5FC5266A93D37B4D6D6171C9931176DC68736629552D8EF0DE174",33445,33445},
{"tox02.ky0uraku.xyz","D3D6D7C0C7009FC75406B0A49E475996C8C4F8BCE1E6FC5967DE427F8F600527",33445,33445},
{"tox.plastiras.org","8E8B63299B3D520FB377FE5100E65E3322F7AE5B20A0ACED2981769FC5B43725",33445,33445},
{"kusoneko.moe","BE7ED53CD924813507BA711FD40386062E6DC6F790EFA122C78F7CDEEE4B6D1B",33445,33445},
{"tox2.plastiras.org","B6626D386BE7E3ACA107B46F48A5C4D522D29281750D44A0CBA6A2721E79C951",33445,33445},
{"172.104.215.182","DA2BD927E01CD05EBCC2574EBE5BEBB10FF59AE0B2105A7D1E2B40E49BB20239",33445,33445},
    { NULL, NULL, 0, 0 }
};


static void hex_string_to_bin2(const char *hex_string, uint8_t *output)
{
    size_t len = strlen(hex_string) / 2;
    size_t i = len;
    if (!output)
    {
        return;
    }
    const char *pos = hex_string;
    for (i = 0; i < len; ++i, pos += 2)
    {
        sscanf(pos, "%2hhx", &output[i]);
    }
}

void boot(Tox *tox) {
    printf("Tox bootstrapping\n");

    for (int i = 0; nodes1[i].ip; i++)
    {
        uint8_t *key = (uint8_t *)calloc(1, 100);
        hex_string_to_bin2(nodes1[i].key, key);
        if (!key)
        {
            continue;
        }

        tox_bootstrap(tox, nodes1[i].ip, nodes1[i].udp_port, key, NULL);

        if (nodes1[i].tcp_port != 0)
        {
            tox_add_tcp_relay(tox, nodes1[i].ip, nodes1[i].tcp_port, key, NULL);
        }
        free(key);
    }
    // ----- bootstrap -----
}

int EMSCRIPTEN_KEEPALIVE wasm_tox_new() {
    struct Tox_Options options;
    tox_options_default(&options);

    // ----- set options ------
    options.ipv6_enabled = true;
    options.local_discovery_enabled = true;
    options.hole_punching_enabled = true;
    options.udp_enabled = true;
    options.tcp_port = 0; // disable tcp relay function!
    // ----- set options ------

    const char *proxy_host = "127.0.0.1";
    uint16_t proxy_port = 33555;
    options.proxy_type = TOX_PROXY_TYPE_SOCKS5;
    options.proxy_host = proxy_host;
    options.proxy_port = proxy_port;

    Tox_Err_New error_tox;
    Tox *tox = tox_new(&options, &error_tox);
    uint8_t my_toxid[100];
    tox_self_get_address(tox, my_toxid);
    char toxid_hex_str[200];
    char toxid_hex[100];
    bin2upHex((const uint8_t *)my_toxid, tox_address_size(), toxid_hex, (tox_address_size() * 2 + 1));
    snprintf(toxid_hex_str, 198, "toxid : %s", toxid_hex);
    emscripten_console_log(toxid_hex_str);
    boot(tox);

    emscripten_console_log("Tox iterating ...");
    tox_iterate(tox, nullptr);
    usleep(1000 * 50);

    emscripten_console_log("Tox iterating ...");
    tox_iterate(tox, nullptr);
    usleep(1000 * 50);

    emscripten_console_log("Tox iterating ...");
    tox_iterate(tox, nullptr);
    usleep(1000 * 50);

    Tox_Err_Friend_Add err1;
    tox_friend_add(tox, (const uint8_t *)"92E052C72D843148389F507A47D60D5275871D8B5FACA869337A216B7AB1DB5623A09B9B6A8E",
        (const uint8_t *)"A", (size_t)1, &err1);
    printf("f_add: %d\n", err1);

    uint8_t msg_id[100];
    char msg_id_hex[100];

    for (int k=0;k<40;k++) {
        tox_messagev3_get_new_message_id((uint8_t *)msg_id);
        bin2upHex((const uint8_t *)msg_id, 32, msg_id_hex, (32 * 2 + 1));
        printf("msgv3id #%d=%s\n", k, msg_id_hex);
    }
    return (int)error_tox;
}

//int main() {
        //emscripten_console_log("main ... 1");
        // emscripten_main_thread_process_queued_calls();
        //emscripten_console_log("main ... 2");
        //return 0;
//}

int answer() {
    return 42;
}

//int answerAsync() {
//    std::future<int> future = std::async(answer);
//    return future.get();
//}

/*
EMSCRIPTEN_BINDINGS(my_module) {
    // function("answer", &answerAsync);
    function("lerp", &lerp);
    function("wasm_tox_version", &wasm_tox_version);
    function("wasm_tox_new", &wasm_tox_new);
    function("wasm_new_message_id", &wasm_new_message_id);
}
*/
