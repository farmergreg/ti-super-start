echo off
call clean
del sstart89\* /Q
del "sstart92+"\* /Q
rd sstart89
rd "sstart92+"
md sstart89
md sstart92+
copy *.c sstart89
copy *.c "sstart92+"
copy *.h sstart89
copy *.h "sstart92+"
copy *.r sstart89
copy *.r "sstart92+"
copy *92p.FSP "sstart92+"
copy *89.FSP sstart89
copy clean.bat sstart89
copy clean.bat "sstart92+"
