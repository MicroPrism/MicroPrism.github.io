
module top_FSM(
	input wire 			sys_clk,
	input wire			sys_rst_n,
	input wire 			pi_money_half,
	input wire 			pi_money_one,

	//output wire			po_money,
	//output wire			po_cola,
	output wire [3:0] 	led
    );
	
	wire fo_money_half;
	wire fo_money_one;
	
	Key_Filter Key_Filter_inst0(
	.sys_clk(sys_clk),
	.sys_rst_n(sys_rst_n),
	
	.key_in(pi_money_half),
	.key_out(fo_money_half)
    );
	Key_Filter Key_Filter_inst1(
	.sys_clk(sys_clk),
	.sys_rst_n(sys_rst_n),
	
	.key_in(pi_money_one),
	.key_out(fo_money_one)
    );
	
	wire [6:0] led_state;
	complex_FSM complex_FSM_inst0(
	.sys_clk(sys_clk),
	.sys_rst_n(sys_rst_n),
	.pi_money_one(fo_money_one),
	.pi_money_half(fo_money_half),
	
	//.po_money(po_money),
	//.po_cola(po_cola),
	.state(led_state)		//对外输出状态
    );
	
	LedCtrl LedCtrl_inst0(
	.sys_clk(sys_clk),
	.sys_rst_n(sys_rst_n),
	.state(led_state),
	
	.led(led)
    );
endmodule
