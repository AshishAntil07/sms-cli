#include "lib.h"
#include "../config.h"

Vec *parse_csv_record(const char *record)
{
  Vec *vec = vec_create(sizeof(char *));
  if (!vec)
    return NULL;

  int is_inside_quotes = 0, cur_i = 0;
  char cur_val[256];
  for (int i = 0; i < strlen(record) + 1; i++)
  {
    if ((record[i] == ',' && !is_inside_quotes) || record[i] == '\0')
    {
      cur_val[cur_i] = '\0';

      char *str = malloc(strlen(cur_val) + 1);
      if (!str)
      {
        vec_free(vec);
        return NULL;
      }
      strcpy(str, cur_val);
      if (vec_push(vec, &str) != 0)
      {
        free(str);
        vec_free(vec);
        return NULL;
      }
      
      cur_i = 0;
      continue;
    }
    else if (record[i] == '"')
    {
      if (!is_inside_quotes)
      {
        is_inside_quotes = 1;
        continue;
      }
      else if (is_inside_quotes)
      {
        if (record[i + 1] == ',' || record[i + 1] == '\0') {
          is_inside_quotes = 0;
          continue;
        }
        else if (record[i + 1] == '"')
        {
          i++;
        }
      }
    }
    cur_val[cur_i++] = record[i];
  }

  return vec;
}

CSVFile *read_student_data(char *fileurl)
{
  CSVFile *csv = malloc(sizeof(CSVFile));
  if (!csv)
  {
    fprintf(stderr, "Memory allocation failed for CSVFile.\n");
    return NULL;
  }

  csv->file = fopen(fileurl == NULL ? OUT_DIR OUT_NAME : fileurl, "r");
  if (!csv->file)
  {
    fprintf(stderr, "Could not open file %s%s for reading.\n", OUT_DIR, OUT_NAME);
    free(csv);
    return NULL;
  }

  Vec *headers = vec_create(sizeof(char *));
  char *headerStr = malloc(256);

  if (!headers || !headerStr)
  {
    fprintf(stderr, "Memory allocation failed for headers vector or header string.\n");
    fclose(csv->file);
    free(csv);
    return NULL;
  }

  fgets(headerStr, strlen(headerStr), csv->file);

  return csv;
}

Student *get_next_student(CSVFile *csv)
{
  if (!csv || !csv->file)
    return NULL;

  Student *student = malloc(sizeof(Student));
  if (!student)
  {
    fprintf(stderr, "Memory allocation failed for student.\n");
    return NULL;
  }

  init_student(student);

  char buffer[256];
  if (fgets(buffer, sizeof(buffer), csv->file) == NULL)
  {
    free(student);
    return NULL; // End of file or error
  }

  // Parse the line into student fields
  // sscanf(buffer, "%[^,],%ld,%c,%[^,],%[^,],%[^,]", student->name, &student->roll, &student->gender, student->phone, student->f_name, student->m_name, student->address);

  return student;
}

void cpy_partial_student(Student *source, Student *dest)
{
  if (!source || !dest)
    return;

  if (source->name)
    dest->name = strdup(source->name);
  if (source->roll)
    dest->roll = source->roll;
  if (source->gender)
    dest->gender = source->gender;
  if (source->phone)
    dest->phone = strdup(source->phone);
  if (source->f_name)
    dest->f_name = strdup(source->f_name);
  if (source->m_name)
    dest->m_name = strdup(source->m_name);
  if (source->address)
    dest->address = strdup(source->address);

  if (source->marks)
  {
    if (dest->marks)
    {
    }
    else
    {
      dest->marks = vec_create(sizeof(Marks));
      if (!dest->marks)
      {
        fprintf(stderr, "Memory allocation failed for student marks vector.\n");
        return;
      }
      vec_copy(source->marks, dest->marks);
    }
  }
}

void write_student_data(Student *student)
{
  FILE *file = fopen(OUT_DIR OUT_NAME, "a");
  if (!file)
  {
    fprintf(stderr, "Could not open file %s%s for writing.\n", OUT_DIR, OUT_NAME);
    return;
  }

  fprintf(file, "%s,%ld,%c,%s,%s,%s,%s\n", student->name, student->roll, student->gender, student->phone, student->f_name, student->m_name, student->address);
  fclose(file);
}

void free_student(Student *student)
{
  if (student)
  {
    free(student->name);
    free(student->phone);
    free(student->f_name);
    free(student->m_name);
    free(student->address);
    free(student);
  }
}

void free_marks(Marks *marks)
{
  if (marks)
  {
    free(marks->subject);
    free(marks);
  }
}

void free_student_data(CSVFile *file)
{
  if (file && file->file)
  {
    fclose(file->file);
    vec_free(file->headers);
    free(file);
  }
}

void init_student(Student *student)
{
  student->name = NULL;
  student->roll = 0;
  student->phone = NULL;
  student->f_name = NULL;
  student->m_name = NULL;
  student->address = NULL;
  student->gender = MALE;
  student->marks = NULL;
}