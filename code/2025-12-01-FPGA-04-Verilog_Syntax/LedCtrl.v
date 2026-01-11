//LED模块只负责根据输入进行输出，流水灯间隔为0.5s
//具体状态由前级状态级给入、包括前级自动切回初始态
module LedCtrl(
	input	wire			sys_clk,
	input	wire			sys_rst_n,
	input	wire	[6:0] 	state,
	
	output	reg		[3:0] 	led
    );
	
	//-------- 全局参数
	parameter	FLOW_TIME_TO_CNT	= 25'd25_000_000;	//流水间隔
	
	//-------- 局部参数
	//LED 状态
	localparam	IDLE 	= 7'b0000001;
	localparam	HALF 	= 7'b0000010;
	localparam	ONE	 	= 7'b0000100;
	localparam	ONE_HALF= 7'b0001000;
	localparam	TWO		= 7'b0010000;
	localparam	TWO_HALF= 7'b0100001;
	localparam	THREE 	= 7'b1000001;
	//计数器局部参数
	localparam	L_GAP_CNT 		= FLOW_TIME_TO_CNT - 1'd1;
	
	//状态输入检测
	reg [6:0] prev_state;
	always@(posedge sys_clk or negedge sys_rst_n)
	if(!sys_rst_n)
		prev_state <= IDLE;
	else
		prev_state <=  state;
	
	//-------- 0.5s流水计数器
	reg	[24:0] unit_cnt;
	always@(posedge sys_clk or negedge sys_rst_n)
	if(!sys_rst_n)
		unit_cnt <= 24'd0;
	else if(state != prev_state)				//状态切换后重新计数
		unit_cnt <= 24'd0;
	else if(unit_cnt == L_GAP_CNT)			//计数满后重新计数
		unit_cnt <= 24'd0;
	else
		unit_cnt <= unit_cnt + 1'd1;
		
	//方向寄存器
	reg flow_dir;
	always@(posedge sys_clk or negedge sys_rst_n)
	if(!sys_rst_n)
		flow_dir <= 1'b0;
	else if(state != prev_state)	/*闪烁过程中状态切换,恢复默认*/
		flow_dir <= 1'b0;
	else if((unit_cnt == L_GAP_CNT)&&(state == THREE))begin
			if(led[2] == 1'b1) 	/*需要提前一拍调转方向*/
				flow_dir <= 1'b1;
			else if(led[1] == 1'b1)
				flow_dir <= 1'b0;
			else
				flow_dir <= flow_dir;
			end
	else
		flow_dir <= flow_dir;
		
	//-------- LED输出
	//LED状态
	localparam	ALL_DARK  = 4'b0000;
	localparam	LIGHT_ONE = 4'b0001;
	localparam	LIGHT_TWO = 4'b0011;
	localparam	LIGHT_THREE = 4'b0111;
	localparam	ALL_LIGHT = 4'b1111;
	
	always@(posedge sys_clk or negedge sys_rst_n)
	if(!sys_rst_n)
		led <= ALL_DARK;
	else if(state != prev_state)	//输入状态改变时刷新
		case(state)
			IDLE:		led <= ALL_DARK;
			HALF:		led <= LIGHT_ONE;
			ONE:		led <= LIGHT_TWO;
			ONE_HALF:	led <= LIGHT_THREE;
			TWO:		led <= ALL_LIGHT;
			TWO_HALF:	led <= LIGHT_ONE;
			THREE:		led <= LIGHT_ONE;
		default:	
			led <= ALL_DARK;
		endcase
	else if(unit_cnt == L_GAP_CNT)
		if(state == TWO_HALF)	/*此处使用case语句会有异常*/
			led <= {led[2:0],led[3]};
		else if(state == THREE)begin		
			if(!flow_dir)
				led <= {led[2:0],led[3]};
			else
				led <= {led[0],led[3:1]};
			end
		else	
			led <= led;
					
endmodule