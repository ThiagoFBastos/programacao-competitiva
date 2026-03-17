import java.util.*

import java.util.Locale

fun main(args: Array<String>) {

	val nota1 = readLine()!!.toDouble()
    val nota2 = readLine()!!.toDouble()

    val media = (3.5 * nota1 + 7.5 * nota2) / 11.0

    println("MEDIA = %.5f".format(Locale.US, media))
}