#
# Filename:	insertion_sort.asm
# Author: 	Remy Jaspres
# Date:		March 1, 2017
# Description:	Insertion sort
	.text
		j	main			# Jump to main-routine

		.data
str1:		.asciiz "Insert the array size \n"
str2:		.asciiz "Insert the array elements,one per line  \n"
str3:		.asciiz "The sorted array is : \n"
str5:		.asciiz "\n"

		.text
		.globl	main
main: 
		la	$a0, str1		# Print of str1
		li	$v0, 4			#
		syscall				#

		li	$v0, 5			# Get the array size(n) and
		syscall				# and put it in $v0
		move	$s2, $v0		# $s2=n
		sll	$s0, $v0, 2		# $s0=n*4
		sub	$sp, $sp, $s0		# This instruction creates a stack
						# frame large enough to contain
						# the array
		la	$a0, str2		#
		li	$v0, 4			# Print of str2
		syscall				#
            
insert:
		addi $a1, $a1, -1		# length - 1
		move $s0, $a1			# j = length -1
		addi $s0, $s0, -1		# j--

	for_insert:
		ble  $s0, $a2, exit_for_insert	# j < i, then exit
		
		sll  $t1, $s0, 2		# $t1 = j * 4
		add  $t2, $a0, $t1		# $t2 = a + (j * 4) = a[j]
		lw   $t3, 4($t2)		# load a[j + 1] in $t3
		sw   $t3, 0($t2)		# store a[j] in t3 = in a[j + 1]
	exit_for_insert:
		sll  $t1, $a3, 2		# i * 4
		add  $t2, $a0, $t1		# $t2 = a + (i * 4) 
		lw   $t3, 0($t2)		# $t3 = a[i]
		sw   $t3, 0($a2)		# a[i] = elem
		j for_insert
binarySearch:
		addi $t0, $t0, -1		# $t0 = low = -1
		move $t1, $a1			# $t1 = high = length
		
		addi $t2, $t1, -1		# $t2 = high - 1
	while_binsearch:
		bge $t0, $t2, exit		# if low >= high - 1, exit
		
		add $t3, $t0, $t1		# $t3 = (low + high)
		srl $t4, $t3, 2			# $t4 = (low + high) / 2 = mid
		
		sll $t4, $t4, 2			# mid * 4
		add $t5, $a0, $t4		# $t5 + (mid * 4) = a[mid]
		lw  $t6, 0($t5)			# $t6 = a[mid]
		j if
	exit_while_binsearch:
	if:	
		blt $t6, $a2, else		# a[mid] < elem, go to else
		move $t1, $t4			# high = mid
	else:   bge $t6, $a2, if		# a[mid] >= elem, go to if
		move $t0, $t4			# low = mid			
		
		move $v0, $t1			# put high in $v0

		move $s1, $zero			# i = 0
insertion_sort:
		bge $s1, $a1, exit		# i >= length, exit
		
		jal binarySearch
		jal insert
		
		bge $s1, $a1, exit		# i >= length, exit
		sll $t0, $s1, 2			# i * 4
	        add $tX, $t0, $zero		# b + (i * 4)
		lw $t2, 0($tX			# $t2 = b[i]
		
		add $t1, $a0, $t0		# a + (i * 4)
		lw  $t3, 0($t1)			# $t3 = a[i]
		
		sw $t3, 0(t2)			# a[i] = b[i]
		lw $t1, 
		
		
		
		move	$s1, $zero		# i=0
for_get:	bge	$s1, $s2, exit_get	# if i>=n go to exit_for_get
		sll	$t0, $s1, 2		# $t0=i*4
		add	$t1, $t0, $sp		# $t1=$sp+i*4
		li	$v0, 5			# Get one element of the array
		syscall				#
		sw	$v0, 0($t1)		# The element is stored
						# at the address $t1
		la	$a0, str5
		li	$v0, 4
		syscall
		addi	$s1, $s1, 1		# i=i+1
		j	for_get
exit_get:	move	$a0, $sp		# $a0=base address af the array
		move	$a1, $s2		# $a1=size of the array
		jal	for_print			# isort(a,n)
						# In this moment the array has been 
						# sorted and is in the stack frame 
		la	$a0, str3		# Print of str3
		li	$v0, 4
		syscall

		move	$s1, $zero		# i=0
for_print:	bge	$s1, $s2, exit_print	# if i>=n go to exit_print
		sll	$t0, $s1, 2		# $t0=i*4
		add	$t1, $sp, $t0		# $t1=address of a[i]
		lw	$a0, 0($t1)		#
		li	$v0, 1			# print of the element a[i]
		syscall				#

		la	$a0, str5
		li	$v0, 4
		syscall
		addi	$s1, $s1, 1		# i=i+1
		j	for_print
exit_print:	add	$sp, $sp, $s0		# elimination of the stack frame 
              
		li	$v0, 10			# EXIT
		syscall				#
