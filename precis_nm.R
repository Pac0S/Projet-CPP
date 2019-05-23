rm(list=ls())


results <- read.table("non_mutation.txt",header=T, sep = '\t')

A <- results$A
T_ <- results$T
state <- results$Etat
max_L_lvg <- results$max_L_lvg


par(mfrow = c(1,1))


library(fields)

An <- unique(A)
Tn <- unique(T_)
dim(state) <- c(101,51)
dim(max_L_lvg)<- c(101,51)



####Etat de cohabitation final####

image.plot(x = Tn, y=An, state, xlab = "T", ylab = "A_init", las = 1,
           main = "Cohabitation des cellules L et S avec P_mut = 0",
           legend.lab = "Extinction tardive\t\t\t\t  Extinction\t\t\tExclusion\t\t\t\tCohabitation")



####Survie des cellules L####

image.plot(x = Tn, y=An, max_L_lvg, xlab = "T", ylab = "A_init", las = 1,
           main = "Survie des cellules L avec P_mut = 0",
           legend.lab = "Extinction imminente\t\t\t\t\t\t\t\t\t\t\t\t\t  Cellules L très majoritaires")




