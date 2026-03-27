import java.util.*
import kotlin.math.absoluteValue

fun maior(a: Int, b: Int): Int = (a + b + (a - b).absoluteValue) / 2

fun main(args: Array<String>) {

    val linha = readLine()!!
    val elementos = linha.split(" ")

    val a = elementos.get(0).toInt()
    val b = elementos.get(1).toInt()
    val c = elementos.get(2).toInt()

    val maior_valor = maior(a, maior(b, c))

    println("$maior_valor eh o maior")
}