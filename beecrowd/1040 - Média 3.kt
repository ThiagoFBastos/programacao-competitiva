import java.util.*

class Console {
    private val buffer = ArrayDeque<String>()

    private fun fillBuffer() {
        if(buffer.isEmpty()) {
            val str = readLine()!!
            val pieces = str.split(" ")

            for (piece in pieces) {
                buffer.add(piece)
            }
        }
    }

    fun readInt(): Int {
        fillBuffer()

        val result = buffer.removeFirst()

        return result.toInt()
    }

    fun readDouble(): Double {
        fillBuffer()

        val result = buffer.removeFirst()

        return result.toDouble()
    }

    fun readString(): String {
        fillBuffer()

        val result = buffer.removeFirst()

        return result
    }

    fun readLong(): Long {
        fillBuffer()

        val result = buffer.removeFirst()

        return result.toLong()
    }

    fun readFloat(): Float {
        fillBuffer()

        val result = buffer.removeFirst()

        return result.toFloat()
    }
}

fun roundToOneDecimalPlace(number: Double): Double = (number * 10).toInt() / 10.0

fun main(args: Array<String>) {

    val console = Console()

    val n1 = console.readDouble()
    val n2 = console.readDouble()
    val n3 = console.readDouble()
    val n4 = console.readDouble()

    val average = (2.0 * n1 + 3.0 * n2 + 4.0 * n3 + n4) / 10.0

    println("Media: %.1f".format(Locale.US, roundToOneDecimalPlace(average)))

    if (average >= 7.0) {
        println("Aluno aprovado.")
    } else if (average < 5.0) {
        println("Aluno reprovado.")
    } else {
        println("Aluno em exame.")

        val nt = console.readDouble()

        println("Nota do exame: %.1f".format(Locale.US, roundToOneDecimalPlace(nt)))

        val ending_average = (nt + average) / 2.0

        if (ending_average >= 5.0) {
            println("Aluno aprovado.")
        } else {
            println("Aluno reprovado.")
        }

        println("Media final: %.1f".format(Locale.US, roundToOneDecimalPlace(ending_average)))
    }
}