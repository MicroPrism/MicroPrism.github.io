module complex_FSM(
	input	wire	sys_clk,
	input	wire	sys_rst_n,
	input 	wire	pi_money_one,
	input	wire	pi_money_half,
	
	//output	reg		po_money,
	//output	reg		po_cola,
	output	reg		[6:0]	state		//对外输出状态
    );
	//------------ 输入合并 ------------------
	wire   [1:0] pi_money;
	assign pi_money = {pi_money_one,pi_money_half};
	
	//------------ 局部参数 ------------------
	//---- 状态定义
	localparam	IDLE 		= 5'b00001;
	localparam	HALF		= 5'b00010;
	localparam	ONE	 		= 5'b00100;
	localparam	ONE_HALF 	= 5'b01000;
	localparam	TWO 		= 5'b10000;
	//-----输入定义
	localparam	INPUT_NULL	= 2'b00;
	localparam	INPUT_HALF	= 2'b01;
	localparam	INPUT_ONE	= 2'b10;
		
	//------------ 复位计数器 ------------------	
	parameter RESET_TIME_TO_CNT = 29'd500_000_000; //默认10s
	reg  [28:0] reset_cnt;
	always@(posedge sys_clk or negedge sys_rst_n)
	if(!sys_rst_n)
		reset_cnt <= 29'd0;
	else if(reset_cnt == RESET_TIME_TO_CNT - 1)	//计数满时清零
		reset_cnt <= 29'd0;
	else if(pi_money != INPUT_NULL)				//切状态时清零
		reset_cnt <= 29'd0;
	else if(state != {2'b00,IDLE})				//状态并非空闲态，开始计数
		reset_cnt <= reset_cnt + 1'd1; 
	else
		reset_cnt <= reset_cnt;
	
	//------------ 状态切换 ------------------	
	always@(posedge sys_clk or negedge sys_rst_n)
	if(!sys_rst_n)
		state <= {2'b00,IDLE};
	else if((reset_cnt == RESET_TIME_TO_CNT - 1)&&(pi_money == INPUT_NULL))
		state <= {2'b00,IDLE};
	else
		case(state[4:0])
		IDLE:	if(pi_money == INPUT_HALF)		//如果新投币，则刷新机器内钱币状态
					state <= {2'b00,HALF};
				else if(pi_money == INPUT_ONE)
					state <= {2'b00,ONE};
				else
					state <= state;				//否则保持原状态，直到计数器复位
		HALF:	if(pi_money == INPUT_HALF)
					state <= {2'b00,ONE};
				else if(pi_money ==INPUT_ONE)
					state <= {2'b00,ONE_HALF};
				else
					state <= state;
		ONE:	if(pi_money == INPUT_HALF)
					state <= {2'b00,ONE_HALF};
				else if(pi_money == INPUT_ONE)
					state <= {2'b00,TWO};
				else 
					state <= state;
		ONE_HALF:if(pi_money == INPUT_HALF)
					state <= {2'b00,TWO};
				else if(pi_money ==INPUT_ONE)
					state  <= {2'b01,IDLE};
				else
					state <= state;
		TWO:	if(pi_money == INPUT_HALF)
					state  <= {2'b01,IDLE};
				else if(pi_money ==INPUT_ONE)
					state  <= {2'b10,IDLE};
				else 
					state <= state;
		default:
				state <= {2'b00,IDLE};
		endcase
	/*
	//---------------- 输出量
	always@(posedge sys_clk or negedge sys_rst_n)
	if(!sys_rst_n)
		po_cola <= 1'b0;
	else if((state == ONE_HALF && pi_money == INPUT_ONE)
			|| (state == TWO && pi_money[1] != pi_money[0]))
		po_cola <= 1'b1;
	else
		po_cola	<= 1'b0;
		
	//---------------- 输出量
	always@(posedge sys_clk or negedge sys_rst_n)
	if(!sys_rst_n)
		po_money <= 1'b0;
	else if(state == TWO && pi_money == INPUT_ONE)
		po_money <= 1'b1;
	else 
		po_money <= 1'b0;
	*/
endmodule
