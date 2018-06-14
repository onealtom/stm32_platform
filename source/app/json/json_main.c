#include "pl_config.h"
#include "chn2freq.h"
#include "formula.h"

#include "json_parse.h"
#include "cJSON.h"

char *content = "{\"LO\":{\"au_ad\":[{\"tx_losc\":0,\"rx_losc\":0},{\"tx_losc\":0,\"rx_losc\":0}],\"ru_ad\":[{\"tx_losc\":874.5,\"rx_losc\":829.5}]},\"SgmtC\":{\"net_std\":\"LTE\",\"ul_dah_thr\":-18,\"ul_adh_thr\":-18,\"ul_dal_thr\":-18,\"ul_adl_thr\":-18,\"dl_adh_thr\":-18,\"dl_dah_thr\":-18,\"dl_adl_thr\":-18,\"dl_dal_thr\":-18,\"au_ad_port\":0,\"ru_ad_port\":0,\"pipe\":[{\"ul_chn\":20400,\"dl_chn\":2400},{\"ul_chn\":20455,\"dl_chn\":2455},{\"ul_chn\":20649,\"dl_chn\":2649}]},\"SgmtD\":{\"net_std\":\"LTE\",\"ul_dah_thr\":-18,\"ul_adh_thr\":-18,\"ul_dal_thr\":-18,\"ul_adl_thr\":-18,\"dl_adh_thr\":-18,\"dl_dah_thr\":-18,\"dl_adl_thr\":-18,\"dl_dal_thr\":-18,\"au_ad_port\":0,\"ru_ad_port\":0,\"pipe\":[{\"ul_chn\":20455,\"dl_chn\":2455}]},\"GainCtlC\":[{\"ul_gain\":36.12,\"ul_alc\":-12,\"dl_gain\":36.12,\"dl_alc\":-12}],\"GainCtlD\":[{\"ul_gain\":36.12,\"ul_alc\":-12,\"dl_gain\":36.12,\"dl_alc\":-12}]}";

int json_main(void)
{
#if 0
	cJSON *parsed = NULL;

	parsed = cJSON_Parse(content);
	printf("cJSON_Parse\r\n");
	char *p ;

	if(!parsed){
		printf("cJSON_Parse return NULL\r\n");
	}
	else{
		printf("############1");
		p = cJSON_Print(parsed);
		printf("%s\n",p);
		cJSON_Delete(parsed);
		free(p);
	}
#endif

	sgmt_parse_then_set(content);
	
	
	
	return 0;
}

