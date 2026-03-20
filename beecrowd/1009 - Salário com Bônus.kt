import java.util.*
import kotlin.math.round

fun roundTwoDecimalPlaces(value: Double) = round(value * 100) / 100.0

fun main(args: Array<String>) {

    val name = readLine()!!
    val fixedSalary = readLine()!!.toDouble()
    val sales = readLine()!!.toDouble()

    val salary = fixedSalary + 0.15 * sales

    println("TOTAL = R$ %.2f".format(Locale.US, roundTwoDecimalPlaces(salary)))
}