import java.util.*

fun main(args: Array<String>) {

    val line = readLine()!!
    val elements = line.split(' ')

    val prices = arrayOf(4.0, 4.5, 5.0, 2.0, 1.5)

    val code = elements[0].toInt()
    val quantity = elements[1].toInt()

    val total_price = prices[code - 1] * quantity

    println("Total: R$ %.2f".format(Locale.US, total_price))
}