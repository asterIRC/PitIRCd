FIRCd v1.1.7 - Fork Created by Matt Ullman (Blindsight)  2014 - Matt@FIRCd.org
===========================================================================

** NOTE FOR THOSE WHO DON'T READ DOCS **

- Reading READ-BEFORE-YOU-INSTALL & INSTALL is now a must, as the old DPATH is now specified when configure is run.
- ALSO, IF YOU ARE UPGRADING YOUR CURRENT SOURCE TREE, AND YOU TRY TO BUILD IN IT WITHOUT PERFORMING AT LEAST 'make clean', THINGS _WILL_ BREAK.  IT IS RECOMMENDED THAT YOU RUN 'make distclean' AND THEN RERUN './configure'!

** OTHER NOTES **

- FIRCd does not compile on FreeBSD as there is an OpenSSL link error. If you know the fix to this,
- please open it up as a pull request and a new version will be released. Currently the only way to
- get it installed on FreeBSD is if you ./configure --disable-openssl

- Files recommended for reading: INSTALL | READ-BEFORE-YOU-INSTALL

- To report bugs in FIRCd, or to talk with the developers visit us at irc.geeksirc.net #FIRCd

- See READ-BEFORE-YOU-INSTALL for a quick install guide as well as additional information

- See the INSTALL document for info on configuring and compiling FIRCd

- SUPPORTED PLATFORMS: this code should compile without any warnings on:
    - Gentoo & Gentoo Hardened ~x86/~amd64/~fbsd
    - Fedora 8/9 / CentOS 4/5 / Redhat Enterprise 5
    - Debian Etch/Lenny/Squeeze
    - OpenSuSE 10/11
    - ArchLinux
    - OpenSolaris 2008.x?
    - Solaris 10 sparc.

- TESTED PLATFORMS:  The code has been tested on the following platforms, and is known to run properly.
    - Linux glibc-2.6, glibc-2.7, glibc-2.8, glibc-2.10, glibc-2.11
    - Solaris 2.6/7/8
    - OpenBSD 2.8
    - NetBSD 1.4
    - OpenVMS/Alpha 7.2 (static modules, no ssld)
