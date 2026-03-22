import java.util.*
import kotlin.math.pow

fun areaTrianguloRetangulo(a: Double, c: Double): Double = a * c / 2.0
fun areaCirculo(c: Double): Double = c.pow(2.0) * 3.14159
fun areaTrapezio(a: Double, b: Double, c: Double): Double = (a + b) * c / 2.0
fun areaQuadrado(b: Double): Double = b.pow(2.0)
fun areaRetangulo(a: Double, b: Double): Double = a * b

fun leTresDoubles(): Triple<Double, Double, Double> {
    val linha = readLine()!!
    val elementos = linha.split(" ")
    val primeiro = elementos[0].toDouble()
    val segundo = elementos[1].toDouble()
    val terceiro = elementos[2].toDouble()

    return Triple(primeiro, segundo, terceiro)
}

fun main(args: Array<String>) {

    val (a, b, c) = leTresDoubles()

    println("TRIANGULO: %.3f".format(Locale.US, areaTrianguloRetangulo(a, c)))
    println("CIRCULO: %.3f".format(Locale.US, areaCirculo(c)))
    println("TRAPEZIO: %.3f".format(Locale.US, areaTrapezio(a, b, c)))
    println("QUADRADO: %.3f".format(Locale.US, areaQuadrado(b)))
    println("RETANGULO: %.3f".format(Locale.US, areaRetangulo(a, b)))
}