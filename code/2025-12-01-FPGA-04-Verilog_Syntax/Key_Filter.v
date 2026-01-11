module Key_Filter(
	input	wire	sys_clk,
	input	wire	sys_rst_n,
	
	input	wire	key_in,
	output	reg		key_out
    );
	
	//----- 全局参数
	parameter	VAILD_TIME_TO_CNT = 20'd1_000_000;	//按键按下有效检测
	
	//----- 局部参数
	localparam	L_VAILD_TIME_TO_CNT = VAILD_TIME_TO_CNT;
	
	//----- 时钟计数器
	reg	[19:0] clk_cnt;
	always@(posedge sys_clk or negedge sys_rst_n)
	if(!sys_rst_n)
		clk_cnt <= 20'b0;
	else if(key_in == 1'b1)
		clk_cnt <= 20'b0;
	else if(clk_cnt == L_VAILD_TIME_TO_CNT)	//计数到指定值后保持
		clk_cnt <= clk_cnt;
	else
		clk_cnt <= clk_cnt + 1'b1;
	
	//------ 按键输出
	//默认输出为高电平，按键按下时输出下降沿
	always@(posedge sys_clk or negedge sys_rst_n)
	if(!sys_rst_n)
		key_out <= 1'b0;
	else if(clk_cnt == L_VAILD_TIME_TO_CNT - 1)
		key_out <= 1'b1;
	else
		key_out <= 1'b0;
		
endmodule
