#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cJSON.h"
#include "pl_config.h"

// typedef struct {
//     uint8_t id;
//     double weight;
//     uint8_t score[8];
//     char name[10];
//     Hometown hometown;
// } Student;



pSGMT_SET_T init_sgmt(char sgmt_no );
pSGMT_GAINCTL_SET_T init_gainctl(char sgmt_no );

char* read_file2string(const char *filename) {
	FILE *file = NULL;
	long length = 0;
	char *content = NULL;
	size_t read_chars = 0;

	/* open in read binary mode */
	file = fopen(filename, "rb");
	if (file == NULL){
		goto cleanup;
	}

	/* get the length */
	if (fseek(file, 0, SEEK_END) != 0){
		goto cleanup;
	}

	length = ftell(file);
	if (length < 0){
		goto cleanup;
	}

	if (fseek(file, 0, SEEK_SET) != 0){
		goto cleanup;
	}

	/* allocate content buffer */
	content = (char*)malloc((size_t)length + sizeof(""));
	if (content == NULL){
		goto cleanup;
	}

	/* read the file into memory */
	read_chars = fread(content, sizeof(char), (size_t)length, file);
	if ((long)read_chars != length){
		free(content);
		content = NULL;
		goto cleanup;
	}
	content[read_chars] = '\0';


cleanup:
	if (file != NULL){
		fclose(file);
	}

	return content;
}

static cJSON *parse_file(const char *filename)
{
	cJSON *parsed = NULL;
	char *content = read_file2string(filename);

	parsed = cJSON_Parse(content);

	if (content != NULL){
		free(content);
	}

	return parsed;
}


inline pSGMT_SET_T init_sgmt(char sgmt_no )
{
	pSGMT_SET_T p_sg=NULL;
	int iCnt;

	
	pr_dbg("sizeof(SGMT_SET_T)=%d\n",sizeof(SGMT_SET_T));

	p_sg = (pSGMT_SET_T)malloc(sizeof(SGMT_SET_T));



	pr_dbg("get point\n");
	
	p_sg->pipe_nr = (uint16_t)get_max_pnr(sgmt_no);

	//pipe结构提指针数组初始化
	// for (iCnt=0;iCnt<MAX_NR_PIPES;iCnt++){
	// 	if(iCnt<(p_sg->pipe_nr)){

	// 		p_sg->pipe_tab[iCnt] = (pPIPE_SET_T)malloc(sizeof(PIPE_SET_T));
	// 	}
	// 	else{
	// 		p_sg->pipe_tab[iCnt] = NULL;
	// 	}
	// }

	p_sg->name = sgmt_no;
	return p_sg;

}

inline pSGMT_GAINCTL_SET_T init_gainctl(char sgmt_no )
{
	pSGMT_GAINCTL_SET_T p_gc;
	int iCnt;

	p_gc = (pSGMT_GAINCTL_SET_T)malloc(sizeof(SGMT_GAINCTL_SET_T));LOG();

	if(p_gc==NULL){
		pr_err("malloc fail\n");
		return NULL;
	}

	p_gc->pipe_nr = get_max_pnr(sgmt_no);

	p_gc->name = sgmt_no;
	return p_gc;

}
/*
parse_lo()    ---<1>
parse_sgmt_X()   ---<2>
parse_gainctl_X()   ---<3>
三组类型的参数解析函数
函数1解析本振LO，AU有两个本振，RU有一个，AU不能设置，RU能设，如果不设，默认本振为内核设备树的值。设置相位字时，需要本振参与计算
函数2解析出段的网络制式，thr，通道的上下行频点号 这些参数，这些参数所有RU都是一样的。
函数3解析alc，gain这些参数，这些参数不同RU不一样，AU没有这些参数。
*/


#define PARSE_SHOW	1
#define PARSE_THEN_SET	2

int parse_lo(cJSON *input)
{
	cJSON *array, *array_element;
        int index = 0, array_size = 0;
        int ul,dl;

	if (is_au())
		array = cJSON_GetObjectItem(input, "au_ad");
	else
		array = cJSON_GetObjectItem(input, "ru_ad");
	//printf("%s\n",cJSON_Print(array));

	if (array) 
		array_size = cJSON_GetArraySize(array);

	//printf("array size is %d\n",array_size);

	int i = 0;
	cJSON *item,*it, *tx_losc, *rx_losc;

	uint32_t u64_tx_losc , u64_rx_losc;

	char *p  = NULL;
	for(i=0; i< array_size; i++) {
		item = cJSON_GetArrayItem(array, i);
		if(!item) {
		//TODO...
		}

		p = cJSON_PrintUnformatted(item);
		it = cJSON_Parse(p);

		if(!it)
			continue ;

		tx_losc = cJSON_GetObjectItem(it, "tx_losc");
		u64_tx_losc = (uint64_t)(1000000*(tx_losc->valuedouble));
		set_tx_lo_clk(i ,u64_tx_losc);

		rx_losc = cJSON_GetObjectItem(it, "rx_losc");
		u64_rx_losc = (uint64_t)(1000000*(rx_losc->valuedouble));
		set_rx_lo_clk(i ,u64_rx_losc);

	}

}

//返回IS_ERROR 参数不全，缺少必要的参数
//net_std和pipe为必要参数，thr和chn
int parse_sgmt_X(cJSON *input , pSGMT_SET_T p_sg)
{

	cJSON *json_tmp;
	int i;

#define	GetThr_Item(x) do { \
	json_tmp = cJSON_GetObjectItem(input, #x); \
	if(json_tmp!=NULL)                         \
		p_sg->x = json_tmp->valueint ;     \
	else                                       \
		p_sg->x = THR_DEFAULTS;            \
}while(0)

	/* 1. parse net_std */
	json_tmp = cJSON_GetObjectItem(input, "net_std");
	if(json_tmp!=NULL)
		p_sg->net_std=json_tmp->valuestring[0];
	else
		return IS_ERROR;

	/* 2. parse xx_xx_losc */
	/* get port num, then get the runtime lo */
	if (is_au()){
		json_tmp = cJSON_GetObjectItem(input, "au_ad_port");
		if(json_tmp!=NULL){
			p_sg->ul_tx_losc = (uint32_t)(get_tx_lo_clk(json_tmp->valueint));
			p_sg->dl_rx_losc = (uint32_t)(get_rx_lo_clk(json_tmp->valueint));

		}else{
			return IS_ERROR;
		}
	}else{
		json_tmp = cJSON_GetObjectItem(input, "ru_ad_port");
		if(json_tmp!=NULL){
			p_sg->dl_tx_losc = (uint32_t)(get_tx_lo_clk(json_tmp->valueint));
			p_sg->ul_rx_losc = (uint32_t)(get_rx_lo_clk(json_tmp->valueint));

		}else{
			return IS_ERROR;
		}	
	}

	/* 3. parse thr */
	json_tmp = cJSON_GetObjectItem(input, "net_std");
	if(json_tmp!=NULL){
		p_sg->net_std=json_tmp->valuestring[0];
	}else{
		return IS_ERROR;	
	}

	GetThr_Item(dl_adh_thr);
	GetThr_Item(dl_adl_thr);
	GetThr_Item(ul_dah_thr);
	GetThr_Item(ul_dal_thr);
	GetThr_Item(ul_adh_thr);
	GetThr_Item(ul_adl_thr);
	GetThr_Item(dl_dah_thr);
	GetThr_Item(dl_dal_thr);

	/* 4. parse pipe_mask */
	json_tmp = cJSON_GetObjectItem(input, "pipe");
	if(json_tmp==NULL){
		return IS_ERROR;	
	}

	int array_size=0;
	char *p  = NULL;
	cJSON *item,*it;
	cJSON *ul_chn,*dl_chn;
	if(json_tmp!=NULL){
		array_size = cJSON_GetArraySize(json_tmp);
	}else{
		array_size = 0;
	}

	p_sg->ul_pipe_mask = (1U<<(array_size))-1;
	p_sg->dl_pipe_mask = (1U<<(array_size))-1;

	pr_dbg("array_size=%d\n",array_size);
	pr_dbg("u=%04X\n",p_sg->ul_pipe_mask);
	pr_dbg("d=%04X\n",p_sg->dl_pipe_mask);

	/* 5. parse pipes */
	for(i=0; i< array_size; i++) {
		item = cJSON_GetArrayItem(json_tmp, i);
		if(!item) {
		//TODO...
		}

		p = cJSON_PrintUnformatted(item);
		it = cJSON_Parse(p);

		if(!it)
			continue ;

		ul_chn = cJSON_GetObjectItem(it, "ul_chn");
		if(ul_chn!=NULL){
			//printf("ul[%d]=%d\n",i, ul_chn->valueint);
			p_sg->pipe_tab[i].ul_chn = (uint32_t)(ul_chn->valueint);
			//printf("ul[%d]=%d\n",i, p_sg->pipe_tab[i].ul_chn);
		}else{
			p_sg->pipe_tab[i].ul_chn = CHN_DEFAULTS;
		}

		dl_chn = cJSON_GetObjectItem(it, "dl_chn");
		if(dl_chn!=NULL){
			//printf("dl[%d]=%d\n",i, dl_chn->valueint);
			p_sg->pipe_tab[i].dl_chn = (uint32_t)(dl_chn->valueint);
			//printf("dl[%d]=%d\n",i, p_sg->pipe_tab[i].dl_chn);	
		}else{
			p_sg->pipe_tab[i].dl_chn = CHN_DEFAULTS;
		}
	}

	return IS_OK;
}


int parse_gainctl_X(cJSON *input , pSGMT_GAINCTL_SET_T p_gc)
{

	int i;
	int array_size=0;
	char *p  = NULL;
	cJSON *item,*it;

	cJSON *ul_alc;
	cJSON *dl_alc;
	cJSON *ul_gain;
	cJSON *dl_gain;

	//p_gc->name=X;

	if (input) 
		array_size = cJSON_GetArraySize(input);

	/*json 配置写了多少个pipe就设多少个pipe的gain alc 参数，
	注释掉，该段有多少个pipe就循环多少次*/
	p_gc->pipe_nr = array_size;

	for(i=0; i< array_size; i++) {
		item = cJSON_GetArrayItem(input, i);
		if(!item) {
		//TODO...
		}

		p = cJSON_PrintUnformatted(item);
		it = cJSON_Parse(p);

		if(!it)
			continue ;

		ul_alc = cJSON_GetObjectItem(it, "ul_alc");
		p_gc->gainctl[i].ul_alc = (uint32_t)(ul_alc->valueint);

		dl_alc = cJSON_GetObjectItem(it, "dl_alc");
		p_gc->gainctl[i].dl_alc = (uint32_t)(dl_alc->valueint);

		ul_gain = cJSON_GetObjectItem(it, "ul_gain");
		p_gc->gainctl[i].ul_gain = (float)(ul_gain->valuedouble);

		dl_gain = cJSON_GetObjectItem(it, "dl_gain");
		p_gc->gainctl[i].dl_gain = (float)(dl_gain->valuedouble);

		pr_dbg("gainctl[%d].ul_alc=%d\n",i, p_gc->gainctl[i].ul_alc);
		pr_dbg("gainctl[%d].dl_alc=%d\n",i, p_gc->gainctl[i].dl_alc);

		pr_dbg("gainctl[%d].ul_gain=%f\n",i, p_gc->gainctl[i].ul_gain);
		pr_dbg("gainctl[%d].dl_gain=%f\n",i, p_gc->gainctl[i].dl_gain);		
	}
}

//返回找到的SgmtX段数
int sgmt_parse_then_set(char * content)
{
	int i;
	cJSON *root = NULL;
	cJSON *json_tmp = NULL;
	int iCnt = 0;

	root = cJSON_Parse(content);
	if (content != NULL){
		free(content);
	}else{
		pr_err("Json Format Error\n");
		return -1;
	}
	/*pipe数组少逗号的格式错误，上面一句不会报错*/
	if (NULL==cJSON_Print(root)){

		pr_err("Json Format Error\n");
		return -1;
	}

	// char sgmt_list[EXTRA_NUMOF_SGMTS];
	// for(i=0;i<EXTRA_NUMOF_SGMTS;i++){
	// 	sgmt_list[i] ='A'+i;
	// }


	pSGMT_SET_T p_sgx;

	//段处理
	char sgmt_json_filename[sizeof("SgmtX")];
	/*在json中查找A～P最多16个段的段名*/
	for(i=0 ; i<EXTRA_NUMOF_SGMTS ; i++){
		//整理文件名
		snprintf(sgmt_json_filename, sizeof("SgmtX"), "Sgmt%c", 'A'+i );
		printf("%s\n",sgmt_json_filename);

		json_tmp = cJSON_GetObjectItem(root, sgmt_json_filename);

		if (!json_tmp){
			pr_dbg("%s not found\n",sgmt_json_filename);
			continue;
		}
		pr_info("Found: %s\n",sgmt_json_filename);
		iCnt++;

		//printf("%s\n",cJSON_Print(json_tmp));

		//json_tmp = cJSON_GetObjectItem(root, "SgmtA");
		json_tmp = cJSON_GetObjectItem(root, sgmt_json_filename);

		p_sgx = init_sgmt('A'+i);
		if ( IS_OK== parse_sgmt_X(json_tmp, p_sgx) ){
			set_thr_regs(p_sgx);
			set_chn_regs(p_sgx);
		}else{
			pr_err("Json missing necessary parameters\n");
		}

		free(p_sgx);

	}

	return iCnt;
}
	
int gainctl_parse_then_set(char * content)
{
	int i;
	cJSON *root = NULL;
	cJSON *json_tmp = NULL;
	int iCnt = 0;
	root = cJSON_Parse(content);
	if (content != NULL){
		free(content);
	}else{
		pr_err("Json Format Error\n");
		return -1;
	}
	/*pipe数组少逗号的格式错误，上面一句不会报错*/
	if (NULL==cJSON_Print(root)){
		pr_err("Json Format Error\n");
		return -1;
	}

	//增益控制处理
	pSGMT_GAINCTL_SET_T p_gcx;

	char gainctl_json_filename[sizeof("GainCtlX")];

	for(i=0 ; i<16 ; i++){
		//整理文件名
		snprintf(gainctl_json_filename, sizeof("GainCtlX"), "GainCtl%c", 'A'+i );

		json_tmp = cJSON_GetObjectItem(root, gainctl_json_filename);

		if (!json_tmp){
			pr_dbg("%s not found\n",gainctl_json_filename);
			continue;
		}
		pr_info("Found: %s\n",gainctl_json_filename);

		json_tmp = cJSON_GetObjectItem(root, gainctl_json_filename);

		p_gcx = init_gainctl('A'+i);

		parse_gainctl_X(json_tmp, p_gcx);

		set_gainalc_regs(p_gcx);

		free(p_gcx);

	}

	return i;

}



