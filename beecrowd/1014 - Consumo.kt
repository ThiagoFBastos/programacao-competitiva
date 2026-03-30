import java.util.*

fun main(args: Array<String>) {

    val quilometros = readLine()!!.toDouble()
    val litros = readLine()!!.toDouble()

    val consumo_medio = quilometros / litros

    println("%.3f km/l".format(Locale.US, consumo_medio))
}