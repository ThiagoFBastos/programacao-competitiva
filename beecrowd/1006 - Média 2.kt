import java.util.*

import java.util.Locale

fun average(n1: Double, n2: Double, n3: Double) = (2.0 * n1 + 3.0 * n2 + 5.0 * n3) / 10.0

fun main(args: Array<String>) {

	val nota1 = readLine()!!.toDouble()
    val nota2 = readLine()!!.toDouble()
    val nota3 = readLine()!!.toDouble()

    println("MEDIA = %.1f".format(Locale.US, average(nota1,nota2,nota3)))
}
