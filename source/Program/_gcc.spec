*startfile:
+ %{stackswap:%{!noixemul:%eYou cannot use -stackswap without using -noixemul} swapstack.o%s}
