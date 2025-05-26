using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using System.Threading.Tasks;
using LMS.Models.LMSModels;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

// For more information on enabling MVC for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace LMS_CustomIdentity.Controllers
{
    [Authorize(Roles = "Professor")]
    public class ProfessorController : Controller
    {

        private readonly LMSContext db;

        public ProfessorController(LMSContext _db)
        {
            db = _db;
        }

        public IActionResult Index()
        {
            return View();
        }

        public IActionResult Students(string subject, string num, string season, string year)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            return View();
        }

        public IActionResult Class(string subject, string num, string season, string year)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            return View();
        }

        public IActionResult Categories(string subject, string num, string season, string year)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            return View();
        }

        public IActionResult CatAssignments(string subject, string num, string season, string year, string cat)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            ViewData["cat"] = cat;
            return View();
        }

        public IActionResult Assignment(string subject, string num, string season, string year, string cat, string aname)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            ViewData["cat"] = cat;
            ViewData["aname"] = aname;
            return View();
        }

        public IActionResult Submissions(string subject, string num, string season, string year, string cat, string aname)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            ViewData["cat"] = cat;
            ViewData["aname"] = aname;
            return View();
        }

        public IActionResult Grade(string subject, string num, string season, string year, string cat, string aname, string uid)
        {
            ViewData["subject"] = subject;
            ViewData["num"] = num;
            ViewData["season"] = season;
            ViewData["year"] = year;
            ViewData["cat"] = cat;
            ViewData["aname"] = aname;
            ViewData["uid"] = uid;
            return View();
        }

        /*******Begin code to modify********/


        /// <summary>
        /// Returns a JSON array of all the students in a class.
        /// Each object in the array should have the following fields:
        /// "fname" - first name
        /// "lname" - last name
        /// "uid" - user ID
        /// "dob" - date of birth
        /// "grade" - the student's grade in this class
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <returns>The JSON array</returns>
       public IActionResult GetStudentsInClass(string subject, int num, string season, int year)
{
    var students = from c in db.Courses
                   join cl in db.Classes on c.CatalogId equals cl.Listing
                   join e in db.Enrolleds on cl.ClassId equals e.Class
                   join s in db.Students on e.Student equals s.UId
                   where c.Department == subject &&
                         c.Number == num &&
                         cl.Season == season &&
                         cl.Year == year
                   select new
                   {
                       fname = s.FName,
                       lname = s.LName,
                       uid = s.UId,
                       dob = s.Dob,
                       grade = e.Grade
                   };

    return Json(students.ToArray());
}




        /// <summary>
        /// Returns a JSON array with all the assignments in an assignment category for a class.
        /// If the "category" parameter is null, return all assignments in the class.
        /// Each object in the array should have the following fields:
        /// "aname" - The assignment name
        /// "cname" - The assignment category name.
        /// "due" - The due DateTime
        /// "submissions" - The number of submissions to the assignment
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class, 
        /// or null to return assignments from all categories</param>
        /// <returns>The JSON array</returns>
       public IActionResult GetAssignmentsInCategory(string subject, int num, string season, int year, string? category)
{
    // Query to fetch assignments based on the given parameters
    var assignmentsQuery = from c in db.Courses
                           join cl in db.Classes on c.CatalogId equals cl.Listing
                           join ac in db.AssignmentCategories on cl.ClassId equals ac.InClass
                           join a in db.Assignments on ac.CategoryId equals a.Category
                           where c.Department == subject &&
                                 c.Number == num &&
                                 cl.Season == season &&
                                 cl.Year == year
                           select new
                           {
                               aname = a.Name,
                               cname = ac.Name,
                               due = a.Due,
                               submissions = a.Submissions.Count()
                           };

    // If a specific category is provided, filter assignments by category
    if (!string.IsNullOrEmpty(category))
    {
        assignmentsQuery = assignmentsQuery.Where(a => a.cname == category);
    }

    // Execute query and return results as JSON
    var assignments = assignmentsQuery.ToArray();
    return Json(assignments);
}



        /// <summary>
        /// Returns a JSON array of the assignment categories for a certain class.
        /// Each object in the array should have the folling fields:
        /// "name" - The category name
        /// "weight" - The category weight
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class</param>
        /// <returns>The JSON array</returns>
        public IActionResult GetAssignmentCategories(string subject, int num, string season, int year)
{
    // Query to fetch assignment categories based on the given parameters
    var categories = from c in db.Courses
                     join cl in db.Classes on c.CatalogId equals cl.Listing
                     join ac in db.AssignmentCategories on cl.ClassId equals ac.InClass
                     where c.Department == subject &&
                           c.Number == num &&
                           cl.Season == season &&
                           cl.Year == year
                     select new
                     {
                         name = ac.Name,
                         weight = ac.Weight
                     };

    // Execute the query and return results as JSON
    var categoryList = categories.ToArray();
    return Json(categoryList);
}


        /// <summary>
        /// Creates a new assignment category for the specified class.
        /// If a category of the given class with the given name already exists, return success = false.
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The new category name</param>
        /// <param name="catweight">The new category weight</param>
        /// <returns>A JSON object containing {success = true/false} </returns>
        public IActionResult CreateAssignmentCategory(string subject, int num, string season, int year, string category, int catweight)
{
    // Step 1: Find the class based on provided course details
    var classInfo = (from c in db.Courses
                     join cl in db.Classes on c.CatalogId equals cl.Listing
                     where c.Department == subject &&
                           c.Number == num &&
                           cl.Season == season &&
                           cl.Year == year
                     select cl).FirstOrDefault();

    if (classInfo == null)
    {
        // Class not found
        return Json(new { success = false, message = "Class not found." });
    }

    // Step 2: Check if the assignment category already exists for this class
    bool categoryExists = db.AssignmentCategories.Any(ac =>
        ac.InClass == classInfo.ClassId &&
        ac.Name == category);

    if (categoryExists)
    {
        // Category already exists
        return Json(new { success = false, message = "Category already exists." });
    }

    // Step 3: Create the new assignment category
    var newCategory = new AssignmentCategory
    {
        Name = category,
        Weight = (uint)catweight,
        InClass = classInfo.ClassId
    };

    db.AssignmentCategories.Add(newCategory);
    db.SaveChanges();

    // Step 4: Return success response
    return Json(new { success = true });
}


        /// <summary>
        /// Creates a new assignment for the given class and category.
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class</param>
        /// <param name="asgname">The new assignment name</param>
        /// <param name="asgpoints">The max point value for the new assignment</param>
        /// <param name="asgdue">The due DateTime for the new assignment</param>
        /// <param name="asgcontents">The contents of the new assignment</param>
        /// <returns>A JSON object containing success = true/false</returns>
       public IActionResult CreateAssignment(string subject, int num, string season, int year, string category, string asgname, int asgpoints, DateTime asgdue, string asgcontents)
{

    // Step 1: Find the class based on provided course details
    var classInfo = (from c in db.Courses
                     join cl in db.Classes on c.CatalogId equals cl.Listing
                     where c.Department == subject &&
                           c.Number == num &&
                           cl.Season == season &&
                           cl.Year == year
                     select cl).FirstOrDefault();

    if (classInfo == null)
    {
        // Class not found
        return Json(new { success = false, message = "Class not found." });
    }

    // Step 2: Find the assignment category
    var categoryInfo = (from ac in db.AssignmentCategories
                        where ac.InClass == classInfo.ClassId &&
                              ac.Name == category
                        select ac).FirstOrDefault();

    if (categoryInfo == null)
    {
        // Assignment category not found
        return Json(new { success = false, message = "Assignment category not found." });
    }

    // Step 3: Create the new assignment
    var newAssignment = new Assignment
    {
        Name = asgname,
        Contents = asgcontents,
        Due = asgdue,
        MaxPoints = (uint)asgpoints,
        Category = categoryInfo.CategoryId
    };

    db.Assignments.Add(newAssignment);
    db.SaveChanges();

    // Step 4: Return success response
    return Json(new { success = true });
}



        /// <summary>
        /// Gets a JSON array of all the submissions to a certain assignment.
        /// Each object in the array should have the following fields:
        /// "fname" - first name
        /// "lname" - last name
        /// "uid" - user ID
        /// "time" - DateTime of the submission
        /// "score" - The score given to the submission
        /// 
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class</param>
        /// <param name="asgname">The name of the assignment</param>
        /// <returns>The JSON array</returns>
  public IActionResult GetSubmissionsToAssignment(string subject, int num, string season, int year, string category, string asgname)
{
    // Step 1: Find the class
    var classInfo = (from c in db.Courses
                     join cl in db.Classes on c.CatalogId equals cl.Listing
                     where c.Department == subject &&
                           c.Number == num &&
                           cl.Season == season &&
                           cl.Year == year
                     select cl).FirstOrDefault();

    if (classInfo == null)
    {
        return Json(new { success = false, message = "Class not found." });
    }

    // Step 2: Find the assignment category
    var categoryInfo = (from ac in db.AssignmentCategories
                        where ac.InClass == classInfo.ClassId &&
                              ac.Name == category
                        select ac).FirstOrDefault();

    if (categoryInfo == null)
    {
        return Json(new { success = false, message = "Assignment category not found." });
    }

    // Step 3: Find the assignment
    var assignmentInfo = (from a in db.Assignments
                          where a.Category == categoryInfo.CategoryId &&
                                a.Name == asgname
                          select a).FirstOrDefault();

    if (assignmentInfo == null)
    {
        return Json(new { success = false, message = "Assignment not found." });
    }

    // Step 4: Retrieve submissions
    var submissions = from s in db.Submissions
                      join st in db.Students on s.Student equals st.UId
                      where s.Assignment == assignmentInfo.AssignmentId
                      select new
                      {
                          fname = st.FName,
                          lname = st.LName,
                          uid = st.UId,
                          time = s.Time,
                          score = s.Score
                      };

    // Step 5: Return JSON array
    return Json(submissions.ToArray());
}



        /// <summary>
        /// Set the score of an assignment submission
        /// </summary>
        /// <param name="subject">The course subject abbreviation</param>
        /// <param name="num">The course number</param>
        /// <param name="season">The season part of the semester for the class the assignment belongs to</param>
        /// <param name="year">The year part of the semester for the class the assignment belongs to</param>
        /// <param name="category">The name of the assignment category in the class</param>
        /// <param name="asgname">The name of the assignment</param>
        /// <param name="uid">The uid of the student who's submission is being graded</param>
        /// <param name="score">The new score for the submission</param>
        /// <returns>A JSON object containing success = true/false</returns>
       public IActionResult GradeSubmission(string subject, int num, string season, int year, string category, string asgname, string uid, int score)
{
    // Find the course based on subject and number
    var course = db.Courses.FirstOrDefault(c => c.Department == subject && c.Number == num);
    if (course == null)
    {
        return Json(new { success = false, message = "Course not found." });
    }

    // Find the class for the given course, season, and year
    var classObj = db.Classes.FirstOrDefault(c =>
        c.Listing == course.CatalogId &&
        c.Season == season &&
        c.Year == year);

    if (classObj == null)
    {
        return Json(new { success = false, message = "Class not found." });
    }

    // Find the assignment category for the given class
    var assignmentCategory = db.AssignmentCategories.FirstOrDefault(ac =>
        ac.InClass == classObj.ClassId &&
        ac.Name == category);

    if (assignmentCategory == null)
    {
        return Json(new { success = false, message = "Assignment category not found." });
    }

    // Find the assignment within the category
    var assignment = db.Assignments.FirstOrDefault(a =>
        a.Category == assignmentCategory.CategoryId &&
        a.Name == asgname);

    if (assignment == null)
    {
        return Json(new { success = false, message = "Assignment not found." });
    }

    // Find the submission made by the student
    var submission = db.Submissions.FirstOrDefault(s =>
        s.Assignment == assignment.AssignmentId &&
        s.Student == uid);

    if (submission == null)
    {
        return Json(new { success = false, message = "Submission not found." });
    }

    // Update the score for the submission
    submission.Score = (uint)score;

    // Save changes to the database
    db.SaveChanges();

    // Update the student's grade based on the new submission score
    UpdateStudentGrade(uid, classObj.ClassId);

    return Json(new { success = true });
}

private string ConvertPercentageToGrade(double cumulativePoints, double totalPoints)
{
    double percentage = totalPoints > 0 ? (cumulativePoints / totalPoints) * 100 : 0;
    // Reference: https://eli.utah.edu/about_the_eli/graduationreq.php#:~:text=University%20Connected%20Learning%20%20%20%20Letter%20Grade,the%20objective
    if (percentage >= 93) return "A";
    if (percentage >= 90) return "A-";
    if (percentage >= 87) return "B+";
    if (percentage >= 83) return "B";
    if (percentage >= 80) return "B-";
    if (percentage >= 77) return "C+";
    if (percentage >= 73) return "C";
    if (percentage >= 70) return "C-";
    if (percentage >= 67) return "D+";
    if (percentage >= 63) return "D";
    if (percentage >= 60) return "D-";
    return "E";
}

private void UpdateStudentGrade(string studentId, uint classId)
{
    // Find the enrollment record for the student in the class
    var enrollment = db.Enrolleds.FirstOrDefault(e =>
        e.Class == classId &&
        e.Student == studentId);

    if (enrollment != null)
    {
        var classObj = enrollment.ClassNavigation;

        // Get all assignment categories for the class
        var assignmentCategories = db.AssignmentCategories.Where(ac => ac.InClass == classObj.ClassId).ToList();

        double cumulativePoints = 0.0;
        double totalPoints = 0.0;

        foreach (var category in assignmentCategories)
        {
            // Get all assignments for the category
            var assignments = db.Assignments.Where(a => a.Category == category.CategoryId).ToList();
            bool hasAssignments = assignments.Count() != 0;

            // Calculate total points earned and total max points for the category
            double categoryTotalPointsEarned = 0.0;
            double categoryTotalMaxPoints = 0.0;

            foreach (var assignment in assignments)
            {
                double assignmentMaxPoints = assignment.MaxPoints;
                categoryTotalMaxPoints += assignmentMaxPoints;

                var submission = db.Submissions.SingleOrDefault(s => s.Assignment == assignment.AssignmentId && s.Student == studentId);
                if (submission != null)
                {
                    double assignmentTotalPoints = (double)submission.Score;
                    categoryTotalPointsEarned += assignmentTotalPoints;
                }
            }

            if (hasAssignments)
            {
                // Calculate the category percentage
                double categoryPercentage = categoryTotalMaxPoints > 0 ? categoryTotalPointsEarned / categoryTotalMaxPoints : 0.0;

                // Scale the category percentage by its weight
                double scaledCategoryTotal = categoryPercentage * category.Weight;

                // Add to cumulative points and total points
                cumulativePoints += scaledCategoryTotal;
                totalPoints += category.Weight;
            }
        }

        // Calculate the final letter grade
        string letterGrade = ConvertPercentageToGrade(cumulativePoints, totalPoints);

        // Update the grade in the enrollment record
        enrollment.Grade = letterGrade;

        // Save changes to the database
        db.SaveChanges();
    }
}


        /// <summary>
        /// Returns a JSON array of the classes taught by the specified professor
        /// Each object in the array should have the following fields:
        /// "subject" - The subject abbreviation of the class (such as "CS")
        /// "number" - The course number (such as 5530)
        /// "name" - The course name
        /// "season" - The season part of the semester in which the class is taught
        /// "year" - The year part of the semester in which the class is taught
        /// </summary>
        /// <param name="uid">The professor's uid</param>
        /// <returns>The JSON array</returns>
  public IActionResult GetMyClasses(string uid)
{
    // Find the professor with the given UID
    var professor = db.Professors.FirstOrDefault(p => p.UId == uid);
    if (professor == null)
    {
        return Json(new { success = false, message = "Professor not found." });
    }

    // Get all classes taught by the professor
    var classes = db.Classes
        .Where(c => c.TaughtBy == uid)
        .Select(c => new 
        {
            subject = c.ListingNavigation.Department,
            number = c.ListingNavigation.Number,
            name = c.ListingNavigation.Name,
            season = c.Season,
            year = c.Year
        })
        .ToList();

    // Return the result as JSON
    return Json(classes);
}

        
        /*******End code to modify********/
    }
}

