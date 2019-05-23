rm(list=ls())



data <- read.table('21.0|831.txt',header = T, sep='\t')

cell_S <- data$S
cell_L <- data$L
temps <- data$temps

plot(x=temps, y=cell_S, col=1, xlab = "Temps", ylab = "Cellules vivantes dans l'environnement",ylim = c(0,1024), main = "Cohabitation des cellules L et S avec A_init = 21 et T = 831",type = "l")
lines(x=temps, y=cell_L, col = 2)
legend("topright", col = c(1,2), legend = c("cellules S","Cellules L"), lty =1)




results <- read.table("global.txt",header=T, sep = '\t')

A <- results$A
T_ <- results$T
state <- results$Etat
nstate <- as.numeric(state) #3 : Extinction, 2 : Exclusion, 1 : Cohabitation




library(fields)


dim(nstate) <- c(13,13)

An <- unique(A)
Tn <- unique(T_)

image.plot(x = Tn, y=An, nstate, xlab = "T", ylab = "A_init", las = 1,
           legend.lab = "Cohabitation \t\t\t\t Exclusion  \t\t\t\t Extinction")



