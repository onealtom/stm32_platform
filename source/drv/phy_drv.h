
#ifndef _PHY_DRV_H_
#define _PHY_DRV_H_
extern UINT16 Phy4_Serdes_St;
/* 覆盖单元PHY 芯片*/
#if 0
#define PHY1_MDC_GPIO			GPIOB
#define PHY1_MDC_PIN			GPIO_Pin_15
#define PHY1_MDIO_GPIO			GPIOB
#define PHY1_MDIO_PIN			GPIO_Pin_14
#define PHY1_RESET_GPIO			GPIOE
#define PHY1_RESET_PIN			GPIO_Pin_6
#define PHY1_SRESET_GPIO		GPIOE
#define PHY1_SRESET_PIN			GPIO_Pin_2

#define PHY2_MDC_GPIO			GPIOE
#define PHY2_MDC_PIN			GPIO_Pin_1
#define PHY2_MDIO_GPIO			GPIOE
#define PHY2_MDIO_PIN			GPIO_Pin_0
#define PHY2_RESET_GPIO			GPIOC
#define PHY2_RESET_PIN			GPIO_Pin_14
#define PHY2_SRESET_GPIO		GPIOC
#define PHY2_SRESET_PIN			GPIO_Pin_13

#define PHY3_MDC_GPIO			GPIOB
#define PHY3_MDC_PIN			GPIO_Pin_9
#define PHY3_MDIO_GPIO			GPIOB
#define PHY3_MDIO_PIN			GPIO_Pin_8
#define PHY3_RESET_GPIO			GPIOC
#define PHY3_RESET_PIN			GPIO_Pin_0
#define PHY3_SRESET_GPIO		GPIOC
#define PHY3_SRESET_PIN			GPIO_Pin_15
#endif

#define PHY4_MDC_GPIO			GPIOD
#define PHY4_MDC_PIN			GPIO_Pin_12
#define PHY4_MDIO_GPIO			GPIOD
#define PHY4_MDIO_PIN			GPIO_Pin_11
#define PHY4_RESET_GPIO			GPIOD
#define PHY4_RESET_PIN			GPIO_Pin_13
#define PHY4_SRESET_GPIO		GPIOE
#define PHY4_SRESET_PIN			GPIO_Pin_6

#define PHY5_MDC_GPIO		GPIOB
#define PHY5_MDC_PIN			GPIO_Pin_10
#define PHY5_MDIO_GPIO		GPIOB
#define PHY5_MDIO_PIN			GPIO_Pin_11
#define PHY5_RESET_GPIO		GPIOA
#define PHY5_RESET_PIN			GPIO_Pin_6
#define PHY5_INT_GPIO		GPIOA
#define PHY5_INT_PIN			GPIO_Pin_7

//扩展单元PHY芯片
#define PHY1_VCS8224_1			0
#define PHY2_VCS8224_2			1
#define PHY3_VCS8601			2
#define PHY4_VCS8662			3
#define PHY5_KSZ9031			5

//函数
void InitPhyIo(void);
void InitPhyfFisrtIo(void);
void InitPhySecondIo(void);
void InitPhyThirdIo(void);
void InitPhyFourthIo(void);
void PhyWrite(UCHAR8 phy_id,UCHAR8 phy_addr,UCHAR8 reg_addr,UINT16 reg_value);
UINT16 PhyRead(UCHAR8 phy_id,UCHAR8 phy_addr,UCHAR8 reg_addr);
UCHAR8 InitPhyReg( UCHAR8 phy_id  );
//void Config_Phy4_Serdes();
//void UplinkHandle();
void PhySmiWriteIo(GPIO_TypeDef* smc_GPIOx, uint16_t smc_GPIO_Pin,
						GPIO_TypeDef* smdio_GPIOx, uint16_t smdio_GPIO_Pin,
						UCHAR8 phy_addr,UCHAR8 reg_addr,UINT16 reg_value);

#endif

