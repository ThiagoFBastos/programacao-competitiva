import java.util.*

fun convertDays(days: Int) {
    var value = days
    val years = value / 365
    value %= 365
    val months = value / 30
    value %= 30
    val days = value

    println("$years ano(s)\n$months mes(es)\n$days dia(s)")
}

fun main(args: Array<String>) {

    val days = readLine()!!.toInt()

    convertDays(days)
}