import java.util.*

fun main(args: Array<String>) {

    val sc = Scanner(System.`in`)

    sc.useLocale(Locale.US)

    val tc = sc.nextInt()

    for (i in 0 until tc) {
        val comida = sc.nextDouble()

        val dias = Math.ceil(Math.log(comida) / Math.log(2.0)).toInt()

        println("$dias dias")
    }
}