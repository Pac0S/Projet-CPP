rm(list=ls())

##################
####Chroniques####
##################

data <- read.table('21.0|831.txt',header = T, sep='\t')

cell_S <- data$S
cell_L <- data$L
temps <- data$temps

plot(x=temps, y=cell_S, col=1, xlab = "Temps", ylab = "Cellules vivantes dans l'environnement",ylim = c(0,1024), main = "Cohabitation des cellules L et S avec A_init = 21 et T = 831",type = "l")
lines(x=temps, y=cell_L, col = 2)
legend("topright", col = c(1,2), legend = c("cellules S","Cellules L"), lty =1)


##########################
####Diagramme de phase####
##########################

results <- read.table("mutation.txt",header=T, sep = '\t')

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
           main = "Cohabitation des cellules L et S avec P_mut = 0.001",
           legend.lab = "Extinction tardive\t\t\t\t  Extinction\t\tExclusion\t\t\t\tCohabitation")



####Survie des cellules L####

image.plot(x = Tn, y=An, max_L_lvg, xlab = "T", ylab = "A_init", las = 1,
           main = "Survie des cellules L avec P_mut = 0.001",
           legend.lab = "Extinction imminente\t\t\t\t\t\t\t\t\t\t\t\t\t  Cellules L très majoritaires")




