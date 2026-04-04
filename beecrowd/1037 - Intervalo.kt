import java.util.*

fun main(args: Array<String>) {

    val number = readLine()!!.toDouble()

    if(number < 0.0) {
        println("Fora de intervalo")
    } else if (number >= 0.0 && number <= 25.0) {
        println("Intervalo [0,25]")
    } else if (number <= 50.0) {
        println("Intervalo (25,50]")
    } else if (number <= 75.0) {
        println("Intervalo (50,75]")
    } else if (number <= 100.0) {
        println("Intervalo (75,100]")
    } else {
        println("Fora de intervalo")
    }
}