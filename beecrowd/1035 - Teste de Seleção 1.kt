import java.util.*

fun canAcceptValues(a: Int, b: Int, c: Int, d: Int): Boolean = b > c && d > a && c + d > a + b && c > 0 && d > 0 && a % 2 == 0

fun main(args: Array<String>) {

    val line = readLine()!!

    val elements = line.split(' ')

    val a = elements[0].toInt()
    val b = elements[1].toInt()
    val c = elements[2].toInt()
    val d = elements[3].toInt()

    if (canAcceptValues(a, b, c, d)) {
        println("Valores aceitos")
    } else {
        println("Valores nao aceitos")
    }
}