import java.util.*
import kotlin.math.pow

fun ehTriangulo(a: Double, b: Double, c: Double): Boolean = a < b + c
fun ehTrianguloRetangulo(a: Double, b: Double, c: Double): Boolean = a.pow(2.0) == b.pow(2.0) + c.pow(2.0)
fun ehTrianguloObtusangulo(a: Double, b: Double, c: Double): Boolean = a.pow(2.0) > b.pow(2.0) + c.pow(2.0)
fun ehTrianguloEquilatero(a: Double, b: Double, c: Double): Boolean = a == b && b == c
fun ehTrianguloIsosceles(a: Double, b: Double, c: Double): Boolean = a == b || a == c || b == c

fun main(args: Array<String>) {

    val sc = Scanner(System.`in`)

    sc.useLocale(Locale.US)

    val lados = ArrayList<Double>()

    for(i in 0..2) {
        val tamanho = sc.nextDouble()
        lados.add(tamanho)
    }

    lados.sort()

    val (c, b, a) = lados

    if(!ehTriangulo(a, b, c)) {
        println("NAO FORMA TRIANGULO")
    } else if(ehTrianguloRetangulo(a, b, c)) {
        println("TRIANGULO RETANGULO")

        if(ehTrianguloIsosceles(a, b, c)) {
            println("TRIANGULO ISOSCELES")
        }
    } else if(ehTrianguloObtusangulo(a, b, c)) {
        println("TRIANGULO OBTUSANGULO")

        if(ehTrianguloIsosceles(a, b, c)) {
            println("TRIANGULO ISOSCELES")
        }
    } else {
        println("TRIANGULO ACUTANGULO")

        if(ehTrianguloEquilatero(a, b, c)) {
            println("TRIANGULO EQUILATERO")
        } else if(ehTrianguloIsosceles(a, b, c)) {
            println("TRIANGULO ISOSCELES")
        }
    }
}