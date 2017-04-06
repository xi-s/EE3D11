library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity memory is
	port
	(
		clk			: in  std_logic;
		rst			: in  std_logic;
		memread			: in  std_logic;
		memwrite		: in  std_logic;
		address1		: in  std_logic_vector (31 downto 0);
		address2		: in  std_logic_vector (31 downto 0);
		writedata		: in  std_logic_vector (31 downto 0);
		instruction		: out std_logic_vector (31 downto 0);
		readdata		: out std_logic_vector (31 downto 0)
	);
end memory;

architecture behavior of memory is
	type ramcell is array (0 to 255) of std_logic_vector (7 downto 0);
	signal ram			: ramcell;
	signal masked1, masked2		: std_logic_vector (7 downto 0);
	signal selector1, selector2	: natural range 0 to 255;
begin
	masked1 <= address1 (7 downto 2) & "00";
	masked2 <= address2 (7 downto 2) & "00";
	selector1 <= to_integer (unsigned (masked1));
	selector2 <= to_integer (unsigned (masked2));

	process (clk, rst, memread, memwrite, address1, address2, writedata)
	begin
		if (rising_edge (clk)) then
			if (rst = '1') then
				ram (  0) <= "11111111"; -- addi  $1,$0,-1
				ram (  1) <= "11111111";
				ram (  2) <= "00000001";
				ram (  3) <= "00100000";
				ram (  4) <= "00000010"; -- addi	$2,$0,2
				ram (  5) <= "00000000";
				ram (  6) <= "00000010";
				ram (  7) <= "00100000";
				ram (  8) <= "00000011"; -- addi	$3,$0,3
				ram (  9) <= "00000000";
				ram ( 10) <= "00000011";
				ram ( 11) <= "00100000";
				ram ( 12) <= "00000110"; -- bgezal $2,DONE
				ram ( 13) <= "00000000";
				ram ( 14) <= "01010001";
				ram ( 15) <= "00000100";
				ram ( 16) <= "00000101"; -- j FAIL
				ram ( 17) <= "00000000";
				ram ( 18) <= "00000000";
				ram ( 19) <= "00001000";
				ram ( 20) <= "01000110"; -- addi  $7,$0,70
				ram ( 21) <= "00000000";
				ram ( 22) <= "00000111";
				ram ( 23) <= "00100000";
				ram ( 24) <= "01000001"; -- addi 	$8,$0,65
				ram ( 25) <= "00000000";
				ram ( 26) <= "00001000";
				ram ( 27) <= "00100000";
				ram ( 28) <= "01001001"; -- addi 	$9,$0,73
				ram ( 29) <= "00000000";
				ram ( 30) <= "00001001";
				ram ( 31) <= "00100000";
				ram ( 32) <= "01001100"; -- addi	$10,$0,76
				ram ( 33) <= "00000000";
				ram ( 34) <= "00001010";
				ram ( 35) <= "00100000";
				ram ( 36) <= "00000000"; -- j TEST
				ram ( 37) <= "00000000";
				ram ( 38) <= "00000000";
				ram ( 39) <= "00001000";
				ram ( 40) <= "01000100"; -- addi   $7,$0,68
				ram ( 41) <= "00000000";
				ram ( 42) <= "00000111";
				ram ( 43) <= "00100000";
				ram ( 44) <= "01001111"; -- addi	$8,$0,79
				ram ( 45) <= "00000000";
				ram ( 46) <= "00001000";
				ram ( 47) <= "00100000";
				ram ( 48) <= "01001110"; -- addi 	$9,$0,78
				ram ( 49) <= "00000000";
				ram ( 50) <= "00001001";
				ram ( 51) <= "00100000";
				ram ( 52) <= "01000101"; -- addi	$10,$0,69
				ram ( 53) <= "00000000";
				ram ( 54) <= "00001010";
				ram ( 55) <= "00100000";
				ram ( 56) <= "00000000"; -- j TEST
				ram ( 57) <= "00000000";
				ram ( 58) <= "00000000";
				ram ( 59) <= "00001000";
				for i in 60 to 255 loop
					ram (i) <= std_logic_vector (to_unsigned (0, 8));
				end loop;
			else
				if (memwrite = '1') then
					ram (selector2 + 0) <= writedata (7 downto 0);
					ram (selector2 + 1) <= writedata (15 downto 8);
					ram (selector2 + 2) <= writedata (23 downto 16);
					ram (selector2 + 3) <= writedata (31 downto 24);
				end if;
			end if;
		end if;
	end process;
	instruction <= ram (selector1 + 3) & ram (selector1 + 2) & ram (selector1 + 1) & ram (selector1 + 0);
	with memread select
		readdata <=	std_logic_vector (to_unsigned (0, 32)) when '0',
				ram (selector2 + 3) & ram (selector2 + 2) & ram (selector2 + 1) & ram (selector2 + 0) when others;
end behavior;
