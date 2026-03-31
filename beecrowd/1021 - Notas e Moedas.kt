import java.util.*

fun main(args: Array<String>) {

    val money = readLine()!!.toDouble()
    var money_times_100 = (money * 100).toInt()

    val banknotes = arrayOf(10000, 5000, 2000, 1000, 500, 200)
    val coins = arrayOf(100, 50, 25, 10, 5, 1)

    println("NOTAS:")

    for (banknote in banknotes) {
        val quantity = money_times_100 / banknote

        money_times_100 %= banknote

        println("$quantity nota(s) de R$ %.2f".format(Locale.US, banknote / 100.0))
    }

    println("MOEDAS:")

    for (coin in coins) {
        val quantity = money_times_100 / coin

        money_times_100 %= coin

        println("$quantity moeda(s) de R$ %.2f".format(Locale.US, coin / 100.0))
    }
}