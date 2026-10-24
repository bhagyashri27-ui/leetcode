/**
 * @param {string} arriveAlice
 * @param {string} leaveAlice
 * @param {string} arriveBob
 * @param {string} leaveBob
 * @return {number}
 */
var countDaysTogether = function(arriveAlice, leaveAlice, arriveBob, leaveBob) {
    const daysInMonth = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];

    // Helper function to convert "MM-DD" into the day of the year (1-365)
    const toDayOfYear = (dateStr) => {
        const month = parseInt(dateStr.slice(0, 2), 10);
        const day = parseInt(dateStr.slice(3, 5), 10);
        
        let totalDays = 0;
        for (let i = 0; i < month - 1; i++) {
            totalDays += daysInMonth[i];
        }
        return totalDays + day;
    };

    // Convert all arrival and departure dates to days of the year
    const startAlice = toDayOfYear(arriveAlice);
    const endAlice = toDayOfYear(leaveAlice);
    const startBob = toDayOfYear(arriveBob);
    const endBob = toDayOfYear(leaveBob);

    // The overlapping interval begins on the later arrival date
    // and ends on the earlier departure date
    const startOverlap = Math.max(startAlice, startBob);
    const endOverlap = Math.min(endAlice, endBob);

    // If startOverlap <= endOverlap, the number of days is (end - start + 1), otherwise 0
    return Math.max(0, endOverlap - startOverlap + 1);
};