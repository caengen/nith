package entity;

import javax.persistence.*;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * User: Cengen
 * Date: 05/12/13
 * Time: 18:37
 */
@Entity
public class User implements Serializable {
    @Id
    private String id;

   @OneToMany (cascade = { CascadeType.ALL })
   private List<Salad> salads;

    public User() {
        salads = new ArrayList<Salad>();
    }

    public User(String id, List<Salad> salads) {
        this.id = id;
        this.salads = salads;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public List<Salad> getSalads() {
        return salads;
    }

    public void setSalads(List<Salad> salads) {
        this.salads = salads;
    }

    public void addSalad(Salad salad) {
        if (salads != null) salads.add(salad);
    }
}
