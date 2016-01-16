apt-get install libblas-dev checkinstall
apt-get install libblas-doc checkinstall
apt-get install liblapacke-dev checkinstall

# this hung the first time, and I had to clean up with:
#  dpkg --configure -a
#  dpkg --remove --force-remove-reinstreq liblapack-doc
#
apt-get install liblapack-doc checkinstall

# ended up installing without checkinstall... am not sure if that made the difference.

------------------
dpkg -L libblas-dev

/.
/usr
/usr/lib
/usr/lib/pkgconfig
/usr/lib/pkgconfig/blas-netlib.pc
/usr/lib/libblas
/usr/lib/libblas/libblas.a
/usr/include
/usr/include/cblas.h
/usr/include/cblas_f77.h
/usr/share
/usr/share/doc
/usr/share/doc/libblas-dev
/usr/share/doc/libblas-dev/copyright
/usr/lib/libblas/libblas.so
/usr/share/doc/libblas-dev/changelog.Debian.gz

------------------

/.
/usr
/usr/share
/usr/share/man
/usr/share/man/man3
/usr/share/man/man3/strsv.3.gz
/usr/share/man/man3/zhpr2.3.gz
/usr/share/man/man3/dsyr2.3.gz
/usr/share/man/man3/sgemm.3.gz
/usr/share/man/man3/zhpmv.3.gz
/usr/share/man/man3/zher.3.gz
/usr/share/man/man3/chemv.3.gz
/usr/share/man/man3/csyrk.3.gz
/usr/share/man/man3/ctbsv.3.gz
/usr/share/man/man3/lsame.3.gz
/usr/share/man/man3/sgemv.3.gz
/usr/share/man/man3/sspmv.3.gz
/usr/share/man/man3/ctrmv.3.gz
/usr/share/man/man3/dsyr.3.gz
/usr/share/man/man3/zsymm.3.gz
/usr/share/man/man3/cher2k.3.gz
/usr/share/man/man3/stpmv.3.gz
/usr/share/man/man3/chbmv.3.gz
/usr/share/man/man3/sgbmv.3.gz
/usr/share/man/man3/ctrmm.3.gz
/usr/share/man/man3/ssymv.3.gz
/usr/share/man/man3/sspr2.3.gz
/usr/share/man/man3/dspr.3.gz
/usr/share/man/man3/zgerc.3.gz
/usr/share/man/man3/dtrsv.3.gz
/usr/share/man/man3/ztrsm.3.gz
/usr/share/man/man3/dsbmv.3.gz
/usr/share/man/man3/chemm.3.gz
/usr/share/man/man3/cgeru.3.gz
/usr/share/man/man3/ztrmv.3.gz
/usr/share/man/man3/dtbmv.3.gz
/usr/share/man/man3/ztbmv.3.gz
/usr/share/man/man3/dspmv.3.gz
/usr/share/man/man3/zher2k.3.gz
/usr/share/man/man3/chpr.3.gz
/usr/share/man/man3/cgbmv.3.gz
/usr/share/man/man3/ssyr2.3.gz
/usr/share/man/man3/xerbla.3.gz
/usr/share/man/man3/csymm.3.gz
/usr/share/man/man3/ssyrk.3.gz
/usr/share/man/man3/zher2.3.gz
/usr/share/man/man3/dcabs1.3.gz
/usr/share/man/man3/zhpr.3.gz
/usr/share/man/man3/zsyr2k.3.gz
/usr/share/man/man3/zherk.3.gz
/usr/share/man/man3/cgerc.3.gz
/usr/share/man/man3/ssyr.3.gz
/usr/share/man/man3/cgemm.3.gz
/usr/share/man/man3/dgemm.3.gz
/usr/share/man/man3/dtrsm.3.gz
/usr/share/man/man3/zgbmv.3.gz
/usr/share/man/man3/ctpsv.3.gz
/usr/share/man/man3/stpsv.3.gz
/usr/share/man/man3/zrotg.3.gz
/usr/share/man/man3/zhbmv.3.gz
/usr/share/man/man3/ztpmv.3.gz
/usr/share/man/man3/dtbsv.3.gz
/usr/share/man/man3/ssbmv.3.gz
/usr/share/man/man3/cher.3.gz
/usr/share/man/man3/cgemv.3.gz
/usr/share/man/man3/strmm.3.gz
/usr/share/man/man3/dsyr2k.3.gz
/usr/share/man/man3/stbmv.3.gz
/usr/share/man/man3/strsm.3.gz
/usr/share/man/man3/cherk.3.gz
/usr/share/man/man3/dspr2.3.gz
/usr/share/man/man3/ztbsv.3.gz
/usr/share/man/man3/ztrmm.3.gz
/usr/share/man/man3/csyr2k.3.gz
/usr/share/man/man3/zgemv.3.gz
/usr/share/man/man3/chpr2.3.gz
/usr/share/man/man3/strmv.3.gz
/usr/share/man/man3/ssyr2k.3.gz
/usr/share/man/man3/zscal.3.gz
/usr/share/man/man3/zgeru.3.gz
/usr/share/man/man3/dsyrk.3.gz
/usr/share/man/man3/dtrmv.3.gz
/usr/share/man/man3/ztpsv.3.gz
/usr/share/man/man3/zhemm.3.gz
/usr/share/man/man3/dgemv.3.gz
/usr/share/man/man3/dsymv.3.gz
/usr/share/man/man3/sspr.3.gz
/usr/share/man/man3/sger.3.gz
/usr/share/man/man3/dtpsv.3.gz
/usr/share/man/man3/dgbmv.3.gz
/usr/share/man/man3/ctrsm.3.gz
/usr/share/man/man3/chpmv.3.gz
/usr/share/man/man3/dtrmm.3.gz
/usr/share/man/man3/dtpmv.3.gz
/usr/share/man/man3/cscal.3.gz
/usr/share/man/man3/zgemm.3.gz
/usr/share/man/man3/stbsv.3.gz
/usr/share/man/man3/cher2.3.gz
/usr/share/man/man3/zsyrk.3.gz
/usr/share/man/man3/ctpmv.3.gz
/usr/share/man/man3/ssymm.3.gz
/usr/share/man/man3/ztrsv.3.gz
/usr/share/man/man3/ctrsv.3.gz
/usr/share/man/man3/dger.3.gz
/usr/share/man/man3/ctbmv.3.gz
/usr/share/man/man3/zhemv.3.gz
/usr/share/man/man3/dsymm.3.gz
/usr/share/doc-base
/usr/share/doc-base/libblas-doc.faq
/usr/share/doc-base/libblas-doc.cinterface
/usr/share/doc
/usr/share/doc/libblas-doc
/usr/share/doc/libblas-doc/blue.png
/usr/share/doc/libblas-doc/cinterface.pdf.gz
/usr/share/doc/libblas-doc/faq.html
/usr/share/doc/libblas-doc/copyright
/usr/share/doc/libblas-doc/changelog.Debian.gz

------------------

/.
/usr
/usr/include
/usr/include/lapacke.h


   lapack_int LAPACKE_sgeev( int matrix_order, char jobvl, char jobvr,
   lapack_int LAPACKE_dgeev( int matrix_order, char jobvl, char jobvr,
   lapack_int LAPACKE_cgeev( int matrix_order, char jobvl, char jobvr,
   lapack_int LAPACKE_zgeev( int matrix_order, char jobvl, char jobvr,
   lapack_int LAPACKE_sggev( int matrix_order, char jobvl, char jobvr,
   lapack_int LAPACKE_dggev( int matrix_order, char jobvl, char jobvr,
   lapack_int LAPACKE_cggev( int matrix_order, char jobvl, char jobvr,
   lapack_int LAPACKE_zggev( int matrix_order, char jobvl, char jobvr,
   lapack_int LAPACKE_chbev( int matrix_order, char jobz, char uplo, lapack_int n,
   lapack_int LAPACKE_zhbev( int matrix_order, char jobz, char uplo, lapack_int n,
   lapack_int LAPACKE_cheev( int matrix_order, char jobz, char uplo, lapack_int n,
   lapack_int LAPACKE_zheev( int matrix_order, char jobz, char uplo, lapack_int n,
   lapack_int LAPACKE_chpev( int matrix_order, char jobz, char uplo, lapack_int n,
   lapack_int LAPACKE_zhpev( int matrix_order, char jobz, char uplo, lapack_int n,
   lapack_int LAPACKE_ssbev( int matrix_order, char jobz, char uplo, lapack_int n,
   lapack_int LAPACKE_dsbev( int matrix_order, char jobz, char uplo, lapack_int n,
   lapack_int LAPACKE_sspev( int matrix_order, char jobz, char uplo, lapack_int n,
   lapack_int LAPACKE_dspev( int matrix_order, char jobz, char uplo, lapack_int n,
   lapack_int LAPACKE_sstev( int matrix_order, char jobz, lapack_int n, float* d,
   lapack_int LAPACKE_dstev( int matrix_order, char jobz, lapack_int n, double* d,
   lapack_int LAPACKE_ssyev( int matrix_order, char jobz, char uplo, lapack_int n,
   lapack_int LAPACKE_dsyev( int matrix_order, char jobz, char uplo, lapack_int n,


/usr/include/lapacke_utils.h
/usr/include/lapacke_mangling.h
/usr/include/lapacke_config.h
/usr/include/lapacke_mangling_with_flags.h
/usr/lib
/usr/lib/liblapacke.a
/usr/share
/usr/share/doc
/usr/share/doc/liblapacke-dev
/usr/share/doc/liblapacke-dev/copyright
/usr/lib/liblapacke.so
/usr/share/doc/liblapacke-dev/changelog.Debian.gz
------------------

