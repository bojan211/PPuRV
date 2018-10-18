
    .global pixelation

    # r0 - pointer to input buffer
    # r1 - pointer to output buffer
    # r2 - size of one line (XSIZE+16)

pixelation:

    push {r4,lr}

    # r4 - iterator (e.g. i)
    mov r4, #0
    # q1 - sum
    vdup.16 q1, r4
    # i = 4;
    mov r4, #4

.loop:
    # load 8 caracters
    vld1.8 {d0}, [r0]
    # increment address of input buffer
    add r0, r0, r2
    # load 8 caracters
    vld1.8 {d1}, [r0]
    # increment address of input buffer
    add r0, r0, r2
    # q1 = d0 + d1
    vaddl.u8 q0, d0, d1
    # q0 = q0 + q1
    vadd.u16 q1, q1, q0
    # i--;
    subs r4, r4, #1
    bne .loop

		# pairwise add
    vpaddl.u16 q1, q1
    # pairwise add
    vpaddl.u32 q1, q1
    vadd.u32 d2, d2, d3 
    vshr.u32 d2, #6
    vmov.u8 r5, d2[0]
    vdup.8 d0, r5
    
    mov r4, #8

.store:

    vst1.8 {d0}, [r1]
    add r1, r1, r2
    subs r4, r4, #1
    bne .store

    pop    {r4, pc }
