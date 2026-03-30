import java.util.*


fun main(args: Array<String>) {

    val horas = readLine()!!.toInt()
    val velocidade = readLine()!!.toInt()
    val quilometros = horas * velocidade
    val litros = quilometros / 12.0

    println("%.3f".format(Locale.US, litros))
}