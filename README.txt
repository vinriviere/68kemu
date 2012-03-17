68Kemu - A CPU emulator for Atari TOS computers
Written in 2010-2012 by Vincent Riviere <vincent.riviere@freesbee.fr>
http://vincent.riviere.free.fr/soft/68kemu/

* Description

This software allows running 68020 TOS programs on a TOS computer featuring a
different physical CPU, such as 68000 or ColdFire.
While the target program itself runs with the emulated CPU, the systems calls
are redirected to the underlying OS where they run natively.
This provides optimal speed and compatibility.

* License

- Usage of 68Kemu binaries is free for any purpose.

- Redistribution of the binaries is allowed for any non-commercial purpose
  It would also be nice to redistribute the sources, but this is not mandatory.
  
- Redistribution in commercial environment is restricted, as stated by the
  Musashi license.

- The 68Kemu main sources are distributed under the CC0 license. Basically,
  this means you are allowed to do anything with them, including reusing them
  in your own software with any license, in source or binary form, for money
  or for free. See COPYING.txt for license details.

- 68Kemu uses the Musashi M680x0 emulator as back-end, which is Copyright
  Karl Stenerud. Basically, it is free for any non-commercial purpose, but
  restrictions apply in commercial environments.
  See readme.txt in 3rd-party/musashi-3.3.1/musashi331.zip for details.
