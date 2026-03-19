import java.util.*

fun main(args: Array<String>) {

    val employeeId = readLine()!!.toInt()
    val workHours = readLine()!!.toInt()
    val salaryByHours = readLine()!!.toDouble()

    val salary = workHours * salaryByHours

    println("NUMBER = $employeeId")
    println("SALARY = U$ %.2f".format(Locale.US, salary))
}
