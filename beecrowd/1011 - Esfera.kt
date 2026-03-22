import java.util.*
import kotlin.math.pow

fun volumeEsphere(r: Double): Double {
    val PI = 3.14159

    return r.pow(3) * (4.0 / 3.0) * PI
}

fun main(args: Array<String>) {

    val radius = readLine()!!.toDouble()

    println("VOLUME = %.3f".format(Locale.US, volumeEsphere(radius)))
}