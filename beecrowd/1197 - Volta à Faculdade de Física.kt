import java.util.*

fun main(args: Array<String>) {

    val sc = Scanner(System.`in`)

    sc.useLocale(Locale.US)

    while(sc.hasNext()) {
        val v = sc.nextInt()
        val t = sc.nextInt()

        val s = 2 * v * t

        println(s)
    }
}