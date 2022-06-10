

#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

void LCD_vInit(void);
void LCD_Send_Command(unsigned char CommandID);
void LCD_Send_Data(char dataID);
void LCD_Send_String( char arr[]);
void LCD_Gotoxy (unsigned char ROWS , unsigned char COL);
void LCD_Send_Float(float num);
void LCD_Send_Num(int num);
void LCD_Clear(void);
















//
//
//typedef struct {
//	u8 portContorl;
//	u8 RS_PIN;
//	u8 E_PIN;
//} LCD_control_T;
//
//typedef struct {
//	u8 portID;
//	LCD_control_T LCD_control;
//} LCD_config_T;
//
///***************************************************************************************/
///* Description! Apply initialization sequence for LCD module                           */
///* Input      ! Nothing                                                                */
///* Output     ! Nothing                                                                */
///***************************************************************************************/
//void LCD_vidInit(LCD_config_T LCD_config);
//
///***************************************************************************************/
///* Description! Interface to send the configuration commands to the LCD Driver         */
///* Input      ! Command number                                                         */
///* Output     ! Nothing                                                                */
///***************************************************************************************/
//void LCD_vidSendCommand(LCD_config_T LCD_config, u8 u8CmdCpy);
//
///***************************************************************************************/
///* Description! Interface to write character on LCD screen                             */
///* Input      ! Data to send                                                           */
///* Output     ! Nothing                                                                */
///***************************************************************************************/
//void LCD_vidWriteCharctr(LCD_config_T LCD_config, u8 u8DataCpy);
//
///***************************************************************************************/
///* Description! Interface to write string on LCD screen                                */
///* Input      ! Pointer to the string                                                  */
///* Output     ! Nothing                                                                */
///***************************************************************************************/
//void LCD_vidWriteString(LCD_config_T LCD_config, u8* pu8StringCpy);
//
//void Gotoxy(LCD_config_T LCD_config, u8 Y, u8 X);
//void LCD_Clear(LCD_config_T LCD_config);
//
#endif /* HAL_LCD_LCD_H_ */
