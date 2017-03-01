#
# Filename:	insertion_sort.asm
# Author: 	Remy Jaspres
# Date:		March 1, 2017
# Description:	Insertion sort
	.text
	j	main			# Jump to main-routine


	.data
insert_str:	.asciiz	"Insert the array size "
elements_str:	.asciiz	"Insert the array elements, one per line"
result_str:	.asciiz	"The sorted array is: "
test_str: 	.asciiz "TEST\n"
newline:	.asciiz	"\n"

	.text
	.globl	main
main:	
	addi	$sp, $sp, -4		# create a stack frame	
	sw	$ra, 0($sp)		# save the return address

	la	$a0, insert_str		# printf("Insert the array size ")
	li	$v0, 	4		#
	syscall				#
	
	li		$v0, 5		# scanf("%d", &n)
	syscall				#
	move		$s0, $v0	# $s0=n
	
	la	$a0, ($s0)		# print getal voor debug
	li	$v0, 1			#
	syscall				#
	
	la	$a0, elements_str	# printf("Insert the array elements, one per line")
	li	$v0, 	4		#
	syscall				#
	
	# FOR #
	move $s1, $zero			
	addi $s2, $zero, 5
for_print:
	bge $s1, $s0, exit_print	# i >= number of array elems.
	sll $t0, $s1, 2			
	add $t1, $sp, $t0
	
	la	$a0, test_str		# printf("Test")
	li	$v0, 	4		#
	syscall				#
	
	addi $s1, $s1, 1
	j for_print
exit_print:
	add $sp, $sp, $s0
	li $v0, 10
	syscall
	# END FOR#
	lw		$ra, 0($sp)	# restore return address	
	addi		$sp, $sp, 4	# eliminate stack frame
	li		$v0, 10		# exit
	syscall

#
# end main
#	
