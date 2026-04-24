import java.util.*
import kotlin.math.absoluteValue

fun main(args: Array<String>) {

    val sc = Scanner(System.`in`)

    sc.useLocale(Locale.US)

    while(sc.hasNext()) {
        val a = sc.nextLong()
        val b = sc.nextLong()

        val diff = (a - b).absoluteValue

        println(diff)
    }
}