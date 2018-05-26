rm(list=ls())

data <- read.table('50.000000|30',header = T, sep='\t')

cell_S <- data$S
cell_L <- data$L
temps <- data$temps

plot(x=temps, y=cell_S, col=1, xlab = "Temps", ylab = "Cellules vivantes dans l'environnement", main = "Cohabitation des cellules L et S avec A_init = 50.0 et T = 30",type = "l")
lines(x=temps, y=cell_L, col = 2)
legend("topright", col = c(1,2), legend = c("cellules S","Cellules L"), lty =1)