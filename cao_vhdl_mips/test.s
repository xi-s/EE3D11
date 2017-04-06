TEST:
	addi  $1, $0, -1 # $1=1
	addi	$2, $0, 2	# $3=1
	addi	$3, $0, 3	# $4=2
	#slt   $5, $2, $3 # if $2 < $3, (1 < 2), $5 will become 1
	bgezal $2, DONE
	#beq	$5, $1, DONE # if condition holds, jump to DONE
	j FAIL
FAIL:
	addi  $7, $0, 70
	addi 	$8, $0, 65
	addi 	$9, $0, 73
	addi	$10, $0, 76
	j TEST	

DONE:
	addi   $7, $0, 68
	addi	$8, $0, 79
	addi 	$9, $0, 78
	addi	$10, $0, 69
	j TEST

