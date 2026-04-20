import java.util.*

fun main(args: Array<String>) {

    val sc = Scanner(System.`in`)

    sc.useLocale(Locale.US)

    val horaInicio = sc.nextInt()
    val horaFinal = sc.nextInt()

    val horas = if(horaInicio < horaFinal) {
        horaFinal - horaInicio
    } else {
        24 - horaInicio + horaFinal
    }

    println("O JOGO DUROU $horas HORA(S)")
}