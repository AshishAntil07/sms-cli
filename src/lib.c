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
        if (record[i + 1] == ',' || record[i + 1] == '\0')
        {
          is_inside_quotes = 0;
          continue;
        }
        else if (record[i + 1] == '"')
        {
          i++;
        }
      }
    }
    if(record[i] != '\n') cur_val[cur_i++] = record[i];
  }

  return vec;
}

CSVFile *read_student_data(char *fileurl)
{
  CSVFile *csv = malloc(sizeof(CSVFile));
  if (!csv)
  {
    printf("read_student_data: Memory allocation failed for CSVFile.\n");
    return NULL;
  }

  csv->file = fopen(fileurl == NULL ? OUT_DIR OUT_NAME : fileurl, "r");
  if (!csv->file)
  {
    printf("read_student_data: Could not open file %s for reading.\n", fileurl == NULL ? OUT_DIR OUT_NAME : fileurl);
    free(csv);
    return NULL;
  }

  char header_str[256];

  if(fileurl) {
    fgets(header_str, sizeof(header_str), csv->file);
  } else {
    strcpy(header_str, "roll,name,gender,phone,f_name,m_name,address");
  }

  csv->headers = parse_csv_record(header_str);

  if (!csv->headers)
  {
    printf("read_student_data: Memory allocation failed for header vector.\n");
    fclose(csv->file);
    free(csv);
    return NULL;
  }

  // if(fileurl) {
  //   printf("%zu\n", csv->headers->size);
  //   printf("header_str: %s\n", header_str);
  //   for (size_t i = 0; i < csv->headers->size; i++)
  //   {
  //     char *header = *(char **)vec_get(csv->headers, i);
  //     if (header)
  //     {
  //       printf("Header %zu: %s\n", i, header);
  //     }
  //   }
  // }

  return csv;
}

Student *get_next_student(CSVFile *csv)
{
  if (!csv || !csv->file)
    return NULL;

  Student *student = malloc(sizeof(Student));
  if (!student)
  {
    printf("get_next_student: Memory allocation failed for student.\n");
    return NULL;
  }

  init_student(student);

  char buffer[256];
  if (fgets(buffer, sizeof(buffer), csv->file) == NULL)
  {
    free(student);
    return NULL;
  }

  Vec *parsed_record = parse_csv_record(buffer);
  if (!parsed_record)
  {
    printf("get_next_student: Failed to parse CSV record.\n");
    free(student);
    return NULL;
  }

  for (size_t i = 0; i < parsed_record->size; i++)
  {
    char *cur_header = lower_case(*(char **)vec_get(csv->headers, i));
    char *value = *(char **)vec_get(parsed_record, i);

    void *property = get_matching_property(student, cur_header);
    if (!property)
    {
      printf("get_next_student: Unknown header '%s' in CSV file. Skipping this header.\n", cur_header);
      continue;
    }

    if(strcmp(cur_header, "roll") == 0) {
      *(long *)property = strtol(value, NULL, 10);
    } else if(strcmp(cur_header, "gender") == 0) {
      *(Gender *)property = *value == 'M' ? MALE : FEMALE;
    } else {
      *(char **)property = value;
    }
  }

  return student;
}

void *get_matching_property(Student *student, const char *property_name)
{
  if (strcmp(property_name, "name") == 0)
    return &student->name;
  else if (strcmp(property_name, "roll") == 0)
    return &student->roll;
  else if (strcmp(property_name, "phone") == 0)
    return &student->phone;
  else if (strcmp(property_name, "f_name") == 0)
    return &student->f_name;
  else if (strcmp(property_name, "m_name") == 0)
    return &student->m_name;
  else if (strcmp(property_name, "address") == 0)
    return &student->address;
  else if (strcmp(property_name, "gender") == 0)
    return &student->gender;
  return NULL;
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
      for(size_t i = 0; i < source->marks->size; i++) {
        Marks *source_marks = (Marks *)vec_get(source->marks, i);
        int is_unique = 1;
        for(size_t j = 0; j < dest->marks->size; j++) {
          Marks *dest_marks = (Marks *)vec_get(dest->marks, j);
          if(dest_marks->student->roll == source_marks->student->roll && dest_marks->subject == source_marks->subject && dest_marks->semester == source_marks->semester) {
            is_unique = 0;
            int choice;
            printf("Colliding marks found for roll no. %ld (%d sem) in subject %s\n  Choose one of the action - (0) retain   (1) override", source_marks->student->roll, source_marks->semester, source_marks->subject);
            scanf("%d", &choice);

            switch(choice) {
              case 0: break;
              case 1: {
                *source_marks = *dest_marks;
                break;
              }
              default: {
                printf("  Didn't match any options, retaining the existing value.\n");
              }
            }
          }
        }
        
        if(is_unique) {
          vec_push(dest->marks, source_marks);
        }
      }
    }
    else
    {
      dest->marks = vec_create(sizeof(Marks));
      if (!dest->marks)
      {
        printf("cpy_partial_student: Memory allocation failed for student marks vector.\n");
        return;
      }
      vec_copy(source->marks, dest->marks);
    }
  }
}

int write_student_data(Student *student)
{
  if(!student) {
    printf("write_student_data: Student is NULL.\n");
    return 1;
  }
  printf("write_student_data: Writing student data for roll no. %ld\n", student->roll);
  FILE *file = fopen(OUT_DIR OUT_NAME, "a");

  if (!file)
  {
    make_dir(OUT_DIR);
    file = fopen(OUT_DIR OUT_NAME, "a");
    if (file == NULL){
      printf("write_student_data: Could not open file %s%s for writing.\n", OUT_DIR, OUT_NAME);
      return 1;
    }
  }

  fprintf(file, "\"%ld\",\"%s\",\"%c\",\"%s\",\"%s\",\"%s\",\"%s\"\n", student->roll, make_csv_friendly(student->name), student->gender, make_csv_friendly(student->phone), make_csv_friendly(student->f_name), make_csv_friendly(student->m_name), make_csv_friendly(student->address));
  fclose(file);

  return 0;
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
  student->name = "";
  student->roll = 0;
  student->phone = "";
  student->f_name = "";
  student->m_name = "";
  student->address = "";
  student->gender = MALE;
  student->marks = NULL;
}