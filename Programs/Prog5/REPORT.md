# Program 5: Memory-Mapped Files
Andrew Avinante
Level: 100
Estimated Time: 3 Hours

## Implemented Features
* All of Level 85
* All of Level 100

## Bugs
* No Known Bugs

## Academic Integrity
*By affixing my signature below, I certify that the accompanying work represents my own intellectual effort. Furthermore, I have received no outside help other than what is documented below and/or in program source code comments.* -Andrew Avinante

## Discussion

### reversemm Output

```
Original                            Copy Reversed
00000160 |B......O.9.....h|         00000000 |R..eF......L....|
00000170 |nV.Amf..H..$t_;.|         00000010 |.;_t$..H..fmA.Vn|
00000180 |....L......Fe..R|         00000020 |h.....9.O......B|

Andrews-Macbook-Pro:Prog5 Andrew$ dd if=/dev/urandom of=original.dat bs=100 count=4
4+0 records in
4+0 records out
400 bytes transferred in 0.000165 secs (2424453 bytes/sec)
Andrews-Macbook-Pro:Prog5 Andrew$ cp original.dat copy.dat
Andrews-Macbook-Pro:Prog5 Andrew$ ./reversemm copy.dat
Andrews-Macbook-Pro:Prog5 Andrew$ ./reversemm copy.dat
Andrews-Macbook-Pro:Prog5 Andrew$ diff original.dat copy.dat
Andrews-Macbook-Pro:Prog5 Andrew$ 
```

### reverscio Output

```
Original                            Copy Reversed
00000160 |...l.G....~...e*|         00000000 |~WU.U...?..l.kQ"|
00000170 |.Wa....Be......X|         00000010 |X......eB....aW.|
00000180 |"Qk.l..?...U.UW~|         00000020 |*e...~....G.l...|

Andrews-Macbook-Pro:Prog5 Andrew$ dd if=/dev/urandom of=original.dat bs=100 count=4
4+0 records in
4+0 records out
400 bytes transferred in 0.000093 secs (4301850 bytes/sec)
Andrews-Macbook-Pro:Prog5 Andrew$ cp original.dat copy.dat
Andrews-Macbook-Pro:Prog5 Andrew$ ./reversecio copy.dat
Andrews-Macbook-Pro:Prog5 Andrew$ ./reversecio copy.dat
Andrews-Macbook-Pro:Prog5 Andrew$ diff original.dat copy.dat
Andrews-Macbook-Pro:Prog5 Andrew$ 
```

### reverseciov2 Output

```
Original                            Copy Reversed
00000160 |...T.......E..t.|         00000000 |.\...{BQg.j..$..|
00000170 |mE;._.?.*..Q0.Z3|         00000010 |3Z.0Q..*.?._.;Em|
00000180 |..$..j.gQB{...\.|         00000020 |.t..E.......T...|

Andrews-Macbook-Pro:Prog5 Andrew$ dd if=/dev/urandom of=original.dat bs=100 count=4
4+0 records in
4+0 records out
400 bytes transferred in 0.000104 secs (3847985 bytes/sec)
Andrews-Macbook-Pro:Prog5 Andrew$ cp original.dat copy.dat
Andrews-Macbook-Pro:Prog5 Andrew$ ./reverseciov2 copy.dat
Andrews-Macbook-Pro:Prog5 Andrew$ ./reverseciov2 copy.dat
Andrews-Macbook-Pro:Prog5 Andrew$ diff original.dat copy.dat
Andrews-Macbook-Pro:Prog5 Andrew$ 

Andrews-Macbook-Pro:Prog5 Andrew$ time ./reverseciov2 2gb.dat

real	0m57.867s
user	0m6.173s
sys	0m24.407s
```