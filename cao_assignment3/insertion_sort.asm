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

		li	$v0, 5			# Get the array length and
		syscall				# and put it in $v0
		move	$s2, $v0		# $s2= length
		sll	$s0, $v0, 2		# $s0 = length * 4
		sub	$sp, $sp, $s0		# This instruction creates a stack
						# frame large enough to contain
						# the array
		la	$a0, str2		#
		li	$v0, 4			# Print of str2
		syscall				#
            
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
		jal	insertion_sort		# isort(a, length)
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

########### INSERT #############
insert:
		addi $t0, $a1, -1		# $t0 = length - 1
	for_insert:
		blt  $t0, $a3, exit_insert	# j < i, then exit
		
		sll  $t1, $t0, 2		# $t1 = j * 4
		add  $t1, $t1, $a0		# $t2 = a + (j * 4) = a[j]
		lw   $t2, 0($t1)		# load a[j] in $t2
		sw   $t2, 4($t1)		# store a[j] in t3 = in a[j + 1]
		
		addi $t0, $t0, -1		# j--
		j for_insert

exit_insert:		
		sll  $t0, $a3, 2		# i * 4 in $t0
		add  $t1, $a0, $t0		# $t2 = a + (i * 4) = a[i]
		sw   $a2, 0($t1)		# a[i] = elem
		jr $ra
		
########### BINSEARCH #############

binsearch:
		addi $t0, $zero, -1		# $t0 = low = -1
		move $t1, $a1			# $t1 = high = length
		
  while_binsearch:
  		addi $t2, $t1, -1		# $t2 = high - 1
		bge $t0, $t2, exit_binsearch	# if low >= high - 1, exit
		
		add $t2, $t0, $t1		# $t2 = (low + high)
		srl $t3, $t2, 1			# $t3 = (low + high) / 2 = mid
		
		sll $t4, $t3, 2			# mid * 4
		add $t4, $t4, $a0		# $t4 + (mid * 4) = a[mid]
		lw  $t4, 0($t4)			# load a[mid] from memory
		
		blt $t4, $a2, else		# a[mid] < elem, go to else
		move $t1, $t3			# high = mid
		j while_binsearch
		
	else:   move $t0, $t3			# low = mid			
		j while_binsearch
exit_binsearch:
		move $v0, $t1			# put high in $v0
		jr $ra			
		
########### Insertion Sort #############

insertion_sort:	addiu  	$sp, $sp, -16		# make room on the stack for 4 items
		sw	$ra, 12($sp)		# save $ra on the stack
		sw	$s0, 8($sp)		# save $s2 on the stack
		sw	$s1, 4($sp)		# save $s1 on the stack
		sw	$s2, 0($sp)		# save $s0 on the stack

		move	$s0, $a1		# $s0 = length
		sll	$t0, $a1, 2		# length * 4 in $t0
		sub	$sp, $sp, $t0		# make room on stack for b
		move	$s1, $sp		# store pointer to b in $s1
		move	$s3, $a0		# $s3 = a[]
		move	$s2, $zero		# i = 0
		
for1:		bge	$s2, $s0, exit_for1	# i >= length, then exit loop
		move	$a0, $s1		# $a0 = b[]
		move	$a1, $s2		# $a1 = i
		sll	$s4, $s2, 2		# $s4 = i * 4
		add	$s4, $s4, $s3		# $s4 = address of a[i]
		lw	$s4, 0($s4)		# $s4 = a[i] from mem
		move	$a2, $s4		# $s2 = a[i]
		jal	binsearch		# call binsearch
		move	$a3, $v0		# move return value $a3, for later use
		jal	insert			# call insert
		addi	$s2, $s2, 1		# i++
		j	for1			# jump to for1
		
exit_for1: 	move	$t0, $zero		# $t0 = i = 0
for2:		bge	$t0, $s0, exit_for2     # i >= length, exit loop
		sll	$t1, $t0, 2		# $t1 = i * 4
		add	$t2, $t1, $s1		# $t2 = address of b[i]
		lw	$t2, 0($t2)		# $t2 = b[i] from mem
		add	$t3, $t1, $s3		# $t3 = a[i] from mem
		sw	$t2, 0($t3)		# a[i] = b[i]($t2)
		addi	$t0, $t0, 1		# i++
		j	for2			# jump to for label
exit_for2:	sll	$t0, $s0, 2		# $t0 = length * 4
		add	$sp, $sp, $t0		# addjust stack
		
		lw	$s2, 0($sp)		# restore $s2 from the stack
		lw	$s1, 4($sp)		# restore $s1 from the stack
		lw	$s0, 8($sp)		# restore $s0 from the stack
		lw	$ra, 12($sp)		# restore $ra from the stack
		
		addiu  	$sp, $sp, 16		# readjust stack for last 4 items
		jr	$ra			# return
