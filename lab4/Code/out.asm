.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
    li $v0, 4
    la $a0, _prompt
    syscall
    li $v0, 5
    syscall
    jr $ra

write:
    li $v0, 1
    syscall
    li $v0, 4
    la $a0, _ret
    syscall
    move $v0, $0
    jr $ra
    
process:
	move  $fp, $sp
	addi  $sp, $fp, -1092
	li  $t1, 4
	sw  $t1, -12($fp)
	lw  $t1, -16($fp)
	lw  $t2, 8($fp)
	li  $t3, 12
	add  $t1, $t2, $t3
	sw  $t1, -16($fp)
	lw  $t1, -16($fp)
	lw  $t2, 8($fp)
	li  $t3, 12
	add  $t1, $t2, $t3
	sw  $t1, -16($fp)
	lw  $t2, -12($fp)
	move  $t1, $t2
	sw  $t1, -12($fp)
	lw  $t1, -36($fp)
	lw  $t2, -12($fp)
	li  $t3, 0
	add  $t1, $t2, $t3
	sw  $t1, -36($fp)
	lw  $t1, -12($fp)
	lw  $t2, -36($fp)
	li  $t3, 0
	sub  $t1, $t2, $t3
	sw  $t1, -12($fp)
	lw  $t1, -52($fp)
	lw  $t2, -12($fp)
	li  $t3, 1
	mul  $t1, $t2, $t3
	sw  $t1, -52($fp)
	lw  $t1, -12($fp)
	lw  $t2, -52($fp)
	li  $t3, 1
	div  $t2, $t3
	mflo  $t1
	sw  $t1, -12($fp)
	lw  $t1, -68($fp)
	lw  $t2, -12($fp)
	li  $t3, 32
	add  $t1, $t2, $t3
	sw  $t1, -68($fp)
	lw  $t1, -84($fp)
	li  $t2, 4
	li  $t3, 7
	mul  $t1, $t2, $t3
	sw  $t1, -84($fp)
	lw  $t1, -80($fp)
	lw  $t2, -84($fp)
	li  $t3, 10
	div  $t2, $t3
	mflo  $t1
	sw  $t1, -80($fp)
	lw  $t1, -12($fp)
	lw  $t2, -68($fp)
	lw  $t3, -80($fp)
	sub  $t1, $t2, $t3
	sw  $t1, -12($fp)
	lw  $t1, -128($fp)
	lw  $t2, 8($fp)
	lw  $t3, -12($fp)
	mul  $t1, $t2, $t3
	sw  $t1, -128($fp)
	lw  $t1, -140($fp)
	lw  $t2, 8($fp)
	lw  $t3, -12($fp)
	mul  $t1, $t2, $t3
	sw  $t1, -140($fp)
	lw  $t1, -124($fp)
	lw  $t2, -128($fp)
	lw  $t3, -140($fp)
	add  $t1, $t2, $t3
	sw  $t1, -124($fp)
	lw  $t1, -152($fp)
	lw  $t2, -12($fp)
	lw  $t3, 8($fp)
	mul  $t1, $t2, $t3
	sw  $t1, -152($fp)
	lw  $t1, -120($fp)
	lw  $t2, -124($fp)
	lw  $t3, -152($fp)
	sub  $t1, $t2, $t3
	sw  $t1, -120($fp)
	lw  $t1, -116($fp)
	lw  $t2, -120($fp)
	lw  $t3, 8($fp)
	sub  $t1, $t2, $t3
	sw  $t1, -116($fp)
	lw  $t1, -168($fp)
	lw  $t2, -12($fp)
	lw  $t3, 8($fp)
	mul  $t1, $t2, $t3
	sw  $t1, -168($fp)
	lw  $t1, -112($fp)
	lw  $t2, -116($fp)
	lw  $t3, -168($fp)
	add  $t1, $t2, $t3
	sw  $t1, -112($fp)
	lw  $t1, -180($fp)
	lw  $t2, -12($fp)
	lw  $t3, -12($fp)
	mul  $t1, $t2, $t3
	sw  $t1, -180($fp)
	lw  $t1, -108($fp)
	lw  $t2, -112($fp)
	lw  $t3, -180($fp)
	add  $t1, $t2, $t3
	sw  $t1, -108($fp)
	lw  $t1, -192($fp)
	lw  $t2, 8($fp)
	lw  $t3, 8($fp)
	div  $t2, $t3
	mflo  $t1
	sw  $t1, -192($fp)
	lw  $t1, -104($fp)
	lw  $t2, -108($fp)
	lw  $t3, -192($fp)
	add  $t1, $t2, $t3
	sw  $t1, -104($fp)
	lw  $t1, -100($fp)
	lw  $t2, -104($fp)
	li  $t3, 12
	sub  $t1, $t2, $t3
	sw  $t1, -100($fp)
	lw  $t1, -208($fp)
	li  $t2, 59
	li  $t3, 2
	div  $t2, $t3
	mflo  $t1
	sw  $t1, -208($fp)
	lw  $t1, -12($fp)
	lw  $t2, -100($fp)
	lw  $t3, -208($fp)
	add  $t1, $t2, $t3
	sw  $t1, -12($fp)
	lw  $t1, -236($fp)
	lw  $t2, -12($fp)
	li  $t3, 3
	mul  $t1, $t2, $t3
	sw  $t1, -236($fp)
	lw  $t1, -248($fp)
	li  $t2, 14
	li  $t3, 24
	mul  $t1, $t2, $t3
	sw  $t1, -248($fp)
	lw  $t1, -232($fp)
	lw  $t2, -236($fp)
	lw  $t3, -248($fp)
	add  $t1, $t2, $t3
	sw  $t1, -232($fp)
	lw  $t1, -264($fp)
	lw  $t2, 8($fp)
	li  $t3, 12
	mul  $t1, $t2, $t3
	sw  $t1, -264($fp)
	lw  $t1, -260($fp)
	lw  $t2, -264($fp)
	li  $t3, 4
	div  $t2, $t3
	mflo  $t1
	sw  $t1, -260($fp)
	lw  $t1, -228($fp)
	lw  $t2, -232($fp)
	lw  $t3, -260($fp)
	sub  $t1, $t2, $t3
	sw  $t1, -228($fp)
	lw  $t1, -280($fp)
	li  $t2, 4
	li  $t3, 5
	mul  $t1, $t2, $t3
	sw  $t1, -280($fp)
	lw  $t1, -224($fp)
	lw  $t2, -228($fp)
	lw  $t3, -280($fp)
	add  $t1, $t2, $t3
	sw  $t1, -224($fp)
	lw  $t1, -292($fp)
	li  $t2, 10
	li  $t3, 2
	mul  $t1, $t2, $t3
	sw  $t1, -292($fp)
	lw  $t1, -220($fp)
	lw  $t2, -224($fp)
	lw  $t3, -292($fp)
	sub  $t1, $t2, $t3
	sw  $t1, -220($fp)
	lw  $t1, -304($fp)
	li  $t2, 5
	li  $t3, 6
	div  $t2, $t3
	mflo  $t1
	sw  $t1, -304($fp)
	lw  $t1, -12($fp)
	lw  $t2, -220($fp)
	lw  $t3, -304($fp)
	sub  $t1, $t2, $t3
	sw  $t1, -12($fp)
	lw  $t1, -12($fp)
	move  $v0, $t1
	jr  $ra
mod:
	move  $fp, $sp
	addi  $sp, $fp, -1092
	lw  $t1, -340($fp)
	lw  $t2, 8($fp)
	lw  $t3, 12($fp)
	div  $t2, $t3
	mflo  $t1
	sw  $t1, -340($fp)
	lw  $t1, -336($fp)
	lw  $t2, -340($fp)
	lw  $t3, 12($fp)
	mul  $t1, $t2, $t3
	sw  $t1, -336($fp)
	lw  $t1, -328($fp)
	lw  $t2, 8($fp)
	lw  $t3, -336($fp)
	sub  $t1, $t2, $t3
	sw  $t1, -328($fp)
	lw  $t1, -328($fp)
	move  $v0, $t1
	jr  $ra
main:
	move  $fp, $sp
	addi  $sp, $fp, -1092
	lw  $t1, -368($fp)
	li  $t2, 4
	li  $t3, 2
	mul  $t1, $t2, $t3
	sw  $t1, -368($fp)
	lw  $t1, -364($fp)
	li  $t2, 0
	lw  $t3, -368($fp)
	sub  $t1, $t2, $t3
	sw  $t1, -364($fp)
	lw  $t1, -360($fp)
	lw  $t2, -364($fp)
	li  $t3, 108
	add  $t1, $t2, $t3
	sw  $t1, -360($fp)
	lw  $t1, -356($fp)
	lw  $t2, -360($fp)
	li  $t3, 17
	div  $t2, $t3
	mflo  $t1
	sw  $t1, -356($fp)
	lw  $t1, -396($fp)
	li  $t2, 32
	li  $t3, 8
	div  $t2, $t3
	mflo  $t1
	sw  $t1, -396($fp)
	lw  $t1, -392($fp)
	lw  $t2, -396($fp)
	li  $t3, 2
	mul  $t1, $t2, $t3
	sw  $t1, -392($fp)
	lw  $t1, -388($fp)
	lw  $t2, -392($fp)
	li  $t3, 1
	sub  $t1, $t2, $t3
	sw  $t1, -388($fp)
	lw  $t1, -428($fp)
	li  $t2, 1
	li  $t3, 4
	mul  $t1, $t2, $t3
	sw  $t1, -428($fp)
	lw  $t1, -424($fp)
	lw  $t2, -428($fp)
	li  $t3, 2
	div  $t2, $t3
	mflo  $t1
	sw  $t1, -424($fp)
	lw  $t1, -416($fp)
	li  $t2, 13
	lw  $t3, -424($fp)
	sub  $t1, $t2, $t3
	sw  $t1, -416($fp)
	lw  $t1, -444($fp)
	lw  $t2, -356($fp)
	lw  $t3, -388($fp)
	add  $t1, $t2, $t3
	sw  $t1, -444($fp)
	lw  $t1, -460($fp)
	lw  $t2, -356($fp)
	lw  $t3, -388($fp)
	add  $t1, $t2, $t3
	sw  $t1, -460($fp)
	lw  $t1, -472($fp)
	lw  $t2, -416($fp)
	li  $t3, 1
	div  $t2, $t3
	mflo  $t1
	sw  $t1, -472($fp)
	lw  $t1, -456($fp)
	lw  $t2, -460($fp)
	lw  $t3, -472($fp)
	add  $t1, $t2, $t3
	sw  $t1, -456($fp)
	lw  $t1, -488($fp)
	lw  $t2, -356($fp)
	lw  $t3, -388($fp)
	mul  $t1, $t2, $t3
	sw  $t1, -488($fp)
	lw  $t1, -484($fp)
	lw  $t2, -488($fp)
	lw  $t3, -416($fp)
	sub  $t1, $t2, $t3
	sw  $t1, -484($fp)
	li  $t1, 42
	sw  $t1, -504($fp)
	li  $t1, 4
	sw  $t1, -508($fp)
	li  $t1, 0
	sw  $t1, -512($fp)
	li  $t1, 0
	sw  $t1, -516($fp)
	lw  $t1, -544($fp)
	lw  $t2, -356($fp)
	lw  $t3, -388($fp)
	add  $t1, $t2, $t3
	sw  $t1, -544($fp)
	lw  $t1, -540($fp)
	lw  $t2, -544($fp)
	lw  $t3, -416($fp)
	add  $t1, $t2, $t3
	sw  $t1, -540($fp)
	lw  $t1, -536($fp)
	lw  $t2, -540($fp)
	li  $t3, 1500
	add  $t1, $t2, $t3
	sw  $t1, -536($fp)
	lw  $t1, -484($fp)
	lw  $t2, -536($fp)
	lw  $t3, -484($fp)
	sub  $t1, $t2, $t3
	sw  $t1, -484($fp)
label1:
	lw  $t1, -512($fp)
	li  $t2, 4
	blt  $t1, $t2, label2
	j  label3
label2:
	lw  $t1, -516($fp)
	li  $t2, 15
	lw  $t3, -512($fp)
	mul  $t1, $t2, $t3
	sw  $t1, -516($fp)
	lw  $t1, -592($fp)
	lw  $t2, -512($fp)
	li  $t3, 4
	mul  $t1, $t2, $t3
	sw  $t1, -592($fp)
	lw  $t1, -596($fp)
	addi  $t2, $fp, -532
	lw  $t3, -592($fp)
	add  $t1, $t2, $t3
	sw  $t1, -596($fp)
	lw  $t2, -516($fp)
	lw  $t1, -596($fp)
	move  $t4, $t2
	sw  $t4, 0($t1)
	lw  $t1, -512($fp)
	lw  $t2, -512($fp)
	li  $t3, 1
	add  $t1, $t2, $t3
	sw  $t1, -512($fp)
	j  label1
label3:
	lw  $t1, -512($fp)
	lw  $t2, -484($fp)
	blt  $t1, $t2, label4
	j  label5
label4:
	lw  $t1, -620($fp)
	lw  $t2, -508($fp)
	lw  $t3, -508($fp)
	mul  $t1, $t2, $t3
	sw  $t1, -620($fp)
	lw  $t1, -644($fp)
	lw  $t2, -504($fp)
	lw  $t3, -620($fp)
	add  $t1, $t2, $t3
	sw  $t1, -644($fp)
	lw  $t1, -656($fp)
	lw  $t2, -512($fp)
	li  $t3, 12
	mul  $t1, $t2, $t3
	sw  $t1, -656($fp)
	lw  $t1, -640($fp)
	lw  $t2, -644($fp)
	lw  $t3, -656($fp)
	add  $t1, $t2, $t3
	sw  $t1, -640($fp)
	lw  $t1, -668($fp)
	li  $t2, 4
	lw  $t3, -508($fp)
	mul  $t1, $t2, $t3
	sw  $t1, -668($fp)
	lw  $t1, -636($fp)
	lw  $t2, -640($fp)
	lw  $t3, -668($fp)
	sub  $t1, $t2, $t3
	sw  $t1, -636($fp)
	lw  $t1, -632($fp)
	lw  $t2, -636($fp)
	li  $t3, 5
	add  $t1, $t2, $t3
	sw  $t1, -632($fp)
	lw  $t1, -684($fp)
	li  $t2, 7
	li  $t3, 3
	div  $t2, $t3
	mflo  $t1
	sw  $t1, -684($fp)
	lw  $t1, -504($fp)
	lw  $t2, -632($fp)
	lw  $t3, -684($fp)
	add  $t1, $t2, $t3
	sw  $t1, -504($fp)
	addi  $sp, $sp, -4
	lw  $t1, -484($fp)
	sw  $t1, 0($sp)
	lw  $t1, -708($fp)
	addi  $sp, $sp, -4
	sw  $ra, 0($sp)
	addi  $sp, $sp, -4
	sw  $fp, 0($sp)
	jal  process
	lw  $ra, 4($fp)
	lw  $fp, 0($fp)
	addi  $sp, $fp, -1092
	move  $t1, $v0
	sw  $t1, -708($fp)
	lw  $t1, -716($fp)
	li  $t2, 2
	lw  $t3, -356($fp)
	mul  $t1, $t2, $t3
	sw  $t1, -716($fp)
	lw  $t1, -704($fp)
	lw  $t2, -708($fp)
	lw  $t3, -716($fp)
	add  $t1, $t2, $t3
	sw  $t1, -704($fp)
	lw  $t1, -700($fp)
	lw  $t2, -704($fp)
	lw  $t3, -484($fp)
	sub  $t1, $t2, $t3
	sw  $t1, -700($fp)
	lw  $t1, -732($fp)
	lw  $t2, -416($fp)
	lw  $t3, -444($fp)
	mul  $t1, $t2, $t3
	sw  $t1, -732($fp)
	lw  $t1, -696($fp)
	lw  $t2, -700($fp)
	lw  $t3, -732($fp)
	add  $t1, $t2, $t3
	sw  $t1, -696($fp)
	addi  $sp, $sp, -4
	li  $t1, 2
	sw  $t1, 0($sp)
	addi  $sp, $sp, -4
	lw  $t1, -484($fp)
	sw  $t1, 0($sp)
	lw  $t1, -744($fp)
	addi  $sp, $sp, -4
	sw  $ra, 0($sp)
	addi  $sp, $sp, -4
	sw  $fp, 0($sp)
	jal  mod
	lw  $ra, 4($fp)
	lw  $fp, 0($fp)
	addi  $sp, $fp, -1092
	move  $t1, $v0
	sw  $t1, -744($fp)
	lw  $t1, -744($fp)
	li  $t2, 0
	bgt  $t1, $t2, label6
	j  label7
label6:
	lw  $t1, -760($fp)
	lw  $t2, -512($fp)
	li  $t3, 3
	add  $t1, $t2, $t3
	sw  $t1, -760($fp)
	lw  $t1, -760($fp)
	lw  $t2, -760($fp)
	li  $t3, 1
	sub  $t1, $t2, $t3
	sw  $t1, -760($fp)
	lw  $t1, -760($fp)
	lw  $t2, -760($fp)
	li  $t3, 3
	add  $t1, $t2, $t3
	sw  $t1, -760($fp)
	lw  $t1, -792($fp)
	li  $t2, 3
	li  $t3, 2
	mul  $t1, $t2, $t3
	sw  $t1, -792($fp)
	lw  $t1, -760($fp)
	lw  $t2, -760($fp)
	lw  $t3, -792($fp)
	sub  $t1, $t2, $t3
	sw  $t1, -760($fp)
label7:
	addi  $sp, $sp, -4
	lw  $t1, -356($fp)
	sw  $t1, 0($sp)
	lw  $t1, -804($fp)
	addi  $sp, $sp, -4
	sw  $ra, 0($sp)
	addi  $sp, $sp, -4
	sw  $fp, 0($sp)
	jal  process
	lw  $ra, 4($fp)
	lw  $fp, 0($fp)
	addi  $sp, $fp, -1092
	move  $t1, $v0
	sw  $t1, -804($fp)
	lw  $t1, -824($fp)
	lw  $t2, -356($fp)
	li  $t3, 3
	add  $t1, $t2, $t3
	sw  $t1, -824($fp)
	lw  $t1, -820($fp)
	lw  $t2, -824($fp)
	li  $t3, 2
	sub  $t1, $t2, $t3
	sw  $t1, -820($fp)
	lw  $t1, -816($fp)
	lw  $t2, -820($fp)
	li  $t3, 1
	sub  $t1, $t2, $t3
	sw  $t1, -816($fp)
	addi  $sp, $sp, -4
	lw  $t1, -816($fp)
	sw  $t1, 0($sp)
	lw  $t1, -812($fp)
	addi  $sp, $sp, -4
	sw  $ra, 0($sp)
	addi  $sp, $sp, -4
	sw  $fp, 0($sp)
	jal  process
	lw  $ra, 4($fp)
	lw  $fp, 0($fp)
	addi  $sp, $fp, -1092
	move  $t1, $v0
	sw  $t1, -812($fp)
	lw  $t1, -804($fp)
	lw  $t2, -812($fp)
	beq  $t1, $t2, label8
	j  label9
label8:
	lw  $t1, -844($fp)
	lw  $t2, -484($fp)
	li  $t3, 2
	sub  $t1, $t2, $t3
	sw  $t1, -844($fp)
	lw  $t1, -484($fp)
	lw  $t2, -844($fp)
	li  $t3, 1
	add  $t1, $t2, $t3
	sw  $t1, -484($fp)
	addi  $sp, $sp, -4
	li  $t1, 4
	sw  $t1, 0($sp)
	addi  $sp, $sp, -4
	lw  $t1, -484($fp)
	sw  $t1, 0($sp)
	lw  $t1, -864($fp)
	addi  $sp, $sp, -4
	sw  $ra, 0($sp)
	addi  $sp, $sp, -4
	sw  $fp, 0($sp)
	jal  mod
	lw  $ra, 4($fp)
	lw  $fp, 0($fp)
	addi  $sp, $fp, -1092
	move  $t1, $v0
	sw  $t1, -864($fp)
	lw  $t1, -876($fp)
	lw  $t2, -864($fp)
	li  $t3, 4
	mul  $t1, $t2, $t3
	sw  $t1, -876($fp)
	lw  $t1, -880($fp)
	addi  $t2, $fp, -532
	lw  $t3, -876($fp)
	add  $t1, $t2, $t3
	sw  $t1, -880($fp)
	addi  $sp, $sp, -4
	li  $t1, 4
	sw  $t1, 0($sp)
	addi  $sp, $sp, -4
	lw  $t1, -484($fp)
	sw  $t1, 0($sp)
	lw  $t1, -904($fp)
	addi  $sp, $sp, -4
	sw  $ra, 0($sp)
	addi  $sp, $sp, -4
	sw  $fp, 0($sp)
	jal  mod
	lw  $ra, 4($fp)
	lw  $fp, 0($fp)
	addi  $sp, $fp, -1092
	move  $t1, $v0
	sw  $t1, -904($fp)
	lw  $t1, -916($fp)
	lw  $t2, -904($fp)
	li  $t3, 4
	mul  $t1, $t2, $t3
	sw  $t1, -916($fp)
	lw  $t1, -920($fp)
	addi  $t2, $fp, -532
	lw  $t3, -916($fp)
	add  $t1, $t2, $t3
	sw  $t1, -920($fp)
	lw  $t2, -920($fp)
	lw  $t1, 0($t2)
	sw  $t1, -896($fp)
	lw  $t1, -892($fp)
	lw  $t2, -896($fp)
	lw  $t3, -760($fp)
	add  $t1, $t2, $t3
	sw  $t1, -892($fp)
	lw  $t1, -888($fp)
	lw  $t2, -892($fp)
	lw  $t3, -696($fp)
	add  $t1, $t2, $t3
	sw  $t1, -888($fp)
	lw  $t1, -884($fp)
	lw  $t2, -888($fp)
	lw  $t3, -456($fp)
	sub  $t1, $t2, $t3
	sw  $t1, -884($fp)
	lw  $t2, -884($fp)
	lw  $t1, -880($fp)
	move  $t4, $t2
	sw  $t4, 0($t1)
label9:
	lw  $t1, -936($fp)
	lw  $t2, -356($fp)
	li  $t3, 2
	add  $t1, $t2, $t3
	sw  $t1, -936($fp)
	lw  $t1, -356($fp)
	lw  $t2, -936($fp)
	li  $t3, 1
	add  $t1, $t2, $t3
	sw  $t1, -356($fp)
	lw  $t1, -512($fp)
	lw  $t2, -512($fp)
	li  $t3, 1
	add  $t1, $t2, $t3
	sw  $t1, -512($fp)
	lw  $t1, -512($fp)
	lw  $t2, -512($fp)
	li  $t3, 1
	add  $t1, $t2, $t3
	sw  $t1, -512($fp)
	j  label3
label5:
	lw  $t1, -356($fp)
	lw  $t2, -356($fp)
	lw  $t3, -388($fp)
	add  $t1, $t2, $t3
	sw  $t1, -356($fp)
	lw  $t1, -388($fp)
	lw  $t2, -356($fp)
	lw  $t3, -388($fp)
	add  $t1, $t2, $t3
	sw  $t1, -388($fp)
	lw  $t1, -416($fp)
	lw  $t2, -356($fp)
	lw  $t3, -388($fp)
	add  $t1, $t2, $t3
	sw  $t1, -416($fp)
	lw  $t1, -484($fp)
	lw  $t2, -356($fp)
	lw  $t3, -388($fp)
	add  $t1, $t2, $t3
	sw  $t1, -484($fp)
	lw  $t1, -696($fp)
	lw  $t2, -356($fp)
	lw  $t3, -388($fp)
	add  $t1, $t2, $t3
	sw  $t1, -696($fp)
	lw  $t1, -1012($fp)
	lw  $t2, -416($fp)
	lw  $t3, -484($fp)
	add  $t1, $t2, $t3
	sw  $t1, -1012($fp)
	lw  $t1, -1008($fp)
	lw  $t2, -1012($fp)
	lw  $t3, -696($fp)
	add  $t1, $t2, $t3
	sw  $t1, -1008($fp)
	addi  $sp, $sp, -4
	sw  $ra, 0($sp)
	lw  $t1, -1008($fp)
	move  $a0, $t1
	jal  write
	lw  $ra, 0($sp)
	addi  $sp, $sp, 4
	addi  $t2, $fp, -532
	move  $t1, $t2
	sw  $t1, -1040($fp)
	lw  $t2, -1040($fp)
	lw  $t1, 0($t2)
	sw  $t1, -1028($fp)
	addi  $sp, $sp, -4
	sw  $ra, 0($sp)
	lw  $t1, -1028($fp)
	move  $a0, $t1
	jal  write
	lw  $ra, 0($sp)
	addi  $sp, $sp, 4
	lw  $t1, -1056($fp)
	addi  $t2, $fp, -532
	li  $t3, 4
	add  $t1, $t2, $t3
	sw  $t1, -1056($fp)
	lw  $t2, -1056($fp)
	lw  $t1, 0($t2)
	sw  $t1, -1044($fp)
	addi  $sp, $sp, -4
	sw  $ra, 0($sp)
	lw  $t1, -1044($fp)
	move  $a0, $t1
	jal  write
	lw  $ra, 0($sp)
	addi  $sp, $sp, 4
	lw  $t1, -1072($fp)
	addi  $t2, $fp, -532
	li  $t3, 8
	add  $t1, $t2, $t3
	sw  $t1, -1072($fp)
	lw  $t2, -1072($fp)
	lw  $t1, 0($t2)
	sw  $t1, -1060($fp)
	addi  $sp, $sp, -4
	sw  $ra, 0($sp)
	lw  $t1, -1060($fp)
	move  $a0, $t1
	jal  write
	lw  $ra, 0($sp)
	addi  $sp, $sp, 4
	lw  $t1, -1088($fp)
	addi  $t2, $fp, -532
	li  $t3, 12
	add  $t1, $t2, $t3
	sw  $t1, -1088($fp)
	lw  $t2, -1088($fp)
	lw  $t1, 0($t2)
	sw  $t1, -1076($fp)
	addi  $sp, $sp, -4
	sw  $ra, 0($sp)
	lw  $t1, -1076($fp)
	move  $a0, $t1
	jal  write
	lw  $ra, 0($sp)
	addi  $sp, $sp, 4
	li  $t1, 0
	move  $v0, $t1
	jr  $ra
