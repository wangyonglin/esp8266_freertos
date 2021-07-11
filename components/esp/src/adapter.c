#include <wangyonglin/esp.h>

esp_err_t objAdapterInit(void)
{
    tcpip_adapter_ip_info_t local_ip;
    esp_err_t err = ESP_OK;
    err = tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_AP, &local_ip);
    tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP);
    IP4_ADDR(&local_ip.ip, 192, 168, 1, 1);
    IP4_ADDR(&local_ip.gw, 192, 168, 1, 1);
    IP4_ADDR(&local_ip.netmask, 255, 255, 255, 0);
    err = tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_AP, &local_ip);
    tcpip_adapter_dhcps_start(TCPIP_ADAPTER_IF_AP);
    return err;
}