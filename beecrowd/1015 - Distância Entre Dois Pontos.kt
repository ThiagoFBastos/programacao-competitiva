import java.util.*
import kotlin.math.pow
import kotlin.math.sqrt

class Point2D {
    private var x: Double = 0.0
    private var y: Double = 0.0

    fun read() {
        val line = readLine()!!
        val elements = line.split(" ")

        x = elements[0].toDouble()
        y = elements[1].toDouble()
    }

    fun distance(rhs: Point2D): Double {
        val dx = x - rhs.x
        val dy = y - rhs.y

        return sqrt(dx.pow(2) + dy.pow(2))
    }
}

fun main(args: Array<String>) {

    val p1 = Point2D()
    val p2 = Point2D()

    p1.read()
    p2.read()

    val distance = p1.distance(p2)

    println("%.4f".format(Locale.US, distance))
}