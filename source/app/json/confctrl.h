#ifndef _CONFCTRL_H
#define _CONFCTRL_H

typedef	struct{
	uint32_t ad;
	unsigned int ln;
}VarField;

typedef VarField * pVarField;


typedef	struct{
	uint32_t pi_chpow;
	uint32_t pi_rgain;
}pipe_cat_var;
typedef pipe_cat_var * p_pipe_cat_var;

typedef	struct{
	//net段采样变量
	uint32_t us_tfpow;
	uint32_t us_comp1;
	uint32_t us_comp2;
	//lo段采样变量
	uint32_t us_comp3;
	uint32_t ds_comp1;
	uint32_t ds_comp2;
	uint32_t ds_comp3;
	uint32_t ds_tfpow;
	//通道采样变量
	pipe_cat_var pi[16];

}lnk_cat_var;

typedef	struct{
	lnk_cat_var *dl;
	lnk_cat_var *ul;
}lnstream_raw;


typedef	struct{

	float ul_us_tfpow;
	float ul_us_comp1;
	float ul_us_comp2;
	float ul_us_comp3;
	float ul_ds_comp1;
	float ul_ds_comp2;
	float ul_ds_comp3;
	float ul_ds_tfpow;

	float dl_us_tfpow;
	float dl_us_comp1;
	float dl_us_comp2;
	float dl_us_comp3;
	float dl_ds_comp1;
	float dl_ds_comp2;
	float dl_ds_comp3;
	float dl_ds_tfpow;

	//通道采样变量
	pipe_cat_var pi[16];

}lnstream_pr;


/* Setting API */
int set_thr_regs(pSGMT_SET_T p_sg);
int set_chn_regs(pSGMT_SET_T p_sg );
int set_gainalc_regs(pSGMT_GAINCTL_SET_T p_gc );

/* Get Status API */


#endif /*_CONFCTRL_H*/