#ifndef  fsm_subscriber_switch
#define fsm_subscriber_switch
#define  switch_count 40
struct fsm_switch_device
{
	unsigned short dev_id;
	unsigned short channel;
	//unsigned char uid[8];
}__attribute__((aligned(4)));

struct fsm_switch_table
{
	struct fsm_switch_device devs[switch_count];
}__attribute__((aligned(4)));

struct fsm_switch_device_config
{
	unsigned short MyMac[4];
	struct fsm_switch_table rs485_st;
	struct fsm_switch_table ble_st;
	struct fsm_switch_table nRFC_st;
} __attribute__((aligned(4)));

struct fsm_switch_subscriber
{
struct fsm_switch_device_config fsmsdc;
} __attribute__((aligned(4)));
#endif
